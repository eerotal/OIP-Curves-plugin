/*
*  Copyright 2017 Eero Talus
*
*  This file is part of Open Image Pipeline Curves plugin.
*
*  Open Image Pipeline Curves plugin is free software: you can redistribute
*  it and/or modify it under the terms of the GNU General Public License
*  as published by the Free Software Foundation, either version 3 of the
*  License, or (at your option) any later version.
*
*  Open Image Pipeline Curves plugin is distributed in the hope that it
*  will be useful, but WITHOUT ANY WARRANTY; without even the implied
*  warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*  See the GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License along
*  with Open Image Pipeline Curves plugin.  If not, see <http://www.gnu.org/licenses/>.
*/

#define PRINT_IDENTIFIER "curves"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "output.h"
#include "plugin.h"
#include "imgutil/imgutil.h"

#define RGBA_BYTES_PER_PIXEL 4

static int curves_process(struct PLUGIN_INDATA *in);
static int curves_setup(void);
static void curves_cleanup(void);
static int curves_apply_function(uint8_t val);
static int curves_ctrl_point_from_str(const char *str);
static int curves_parse_args(char **args, int argc);

// Valid plugin arguments
static const char *curves_valid_args[2] = {
	"ctrl_points",
	"channels"
};

// Plugin information
PLUGIN_INFO PLUGIN_INFO_NAME(curves) = {
	.name = "curves",
	.descr = "A curve based image manipulation plugin.",
	.author = "Eero Talus",
	.year = "2017",

	.valid_args = curves_valid_args,
	.valid_args_count = 2,

	.flag_print_verbose = &print_verbose,

	.plugin_process = &curves_process,
	.plugin_setup = &curves_setup,
	.plugin_cleanup = &curves_cleanup
};

static struct ENABLED_CHANNELS {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
	uint8_t l;
} enabled_channels = {0, 0, 0, 0, 0};

static uint8_t *ctrl_points = NULL;
static uint8_t num_ctrl_points = 0;

static int curves_apply_function(uint8_t val) {
	/*
	*  Apply the piecewise mathematical function defined
	*  by the control points on val and return the result
	*  clipped to 0-255.
	*/
	long int res = 0;
	uint8_t dx = 0;
	uint8_t dy = 0;
	float a = 0;
	float b = 0;

	for (unsigned int i = 1; i < num_ctrl_points; i++) {
		if (val > ctrl_points[(i - 1)*2] && val <= ctrl_points[i*2]) {
			/*
			*  Calculate the slope of the line between two consequent
			*  control points.
			*/
			dx = ctrl_points[i*2] - ctrl_points[(i - 1)*2];
			dy = ctrl_points[i*2 + 1] - ctrl_points[(i - 1)*2 + 1];
			a = (float) dy/dx;

			/*
			*  By some math wizardry it can be found out that
			*  the constant term of the line between two consequent
			*  points is b=-a*x_0+y_0 where (x_0, y_0) is one of
			*  the original points.
			*/
			b = -a*ctrl_points[i*2] + ctrl_points[i*2 + 1];
			break;
		}
	}

	res = a*val + b;
	if (res > 255) {
		return 255;
	} else if (res < 0) {
		return 0;
	}
	return res;
}

static int curves_ctrl_point_from_str(const char *str) {
	uint8_t *tmp_ctrl_points = NULL;
	char *tmp_str = NULL;
	long int x = 0;
	long int y = 0;

	if (str == NULL) {
		return 1;
	}

	/*
	*  Convert the coordinates from the
	*  string that's of the form "x,y".
	*/
	x = strtol(str, &tmp_str, 10);
	y = strtol(tmp_str + 1, NULL, 10);

	// Clip control points to 0-255.
	if (x > 255) {
		x = 255;
	} else if (x < 0) {
		x = 0;
	}
	if (y > 255) {
		y = 255;
	} else if (y < 0) {
		y = 0;
	}

	printverb_va("Adding control point (%li, %li).\n", x, y);

	// Add the control points to the control point array.
	num_ctrl_points++;
	tmp_ctrl_points = realloc(ctrl_points, num_ctrl_points*2*sizeof(uint8_t));
	if (tmp_ctrl_points == NULL) {
		num_ctrl_points--;
		return 1;
	}
	ctrl_points = tmp_ctrl_points;

	ctrl_points[(num_ctrl_points - 1)*2] = x;
	ctrl_points[(num_ctrl_points - 1)*2 + 1] = y;

	return 0;
}

static int curves_parse_args(char **args, int argc) {
	/*
	*  Parse the plugin args. Return 0 on success
	*  and 1 on failure.
	*/
	char *tmp_arg = NULL;
	char *tmp_val = NULL;
	unsigned int no_channels_enabled = 1;

	for (unsigned int i = 0; i < argc; i++) {
		tmp_arg = (char*) args[i*2];
		tmp_val = (char*) args[i*2 + 1];
		if (strcmp(tmp_arg, "ctrl_points") == 0) {
			for (int c = 0; c < strlen(tmp_val); c++) {
				if (tmp_val[c] == '(') {
					if (curves_ctrl_point_from_str(tmp_val + c + 1) != 0) {
						return 1;
					}
				}
			}
		} else if (strcmp(tmp_arg, "channels") == 0) {
			memset(&enabled_channels, 0, sizeof(struct ENABLED_CHANNELS));
			printverb("Enabled channels: ");
			for (int c = 0; c < strlen(tmp_val); c++) {
				switch (tmp_val[c]) {
					case 'R':
						enabled_channels.r = 1;
						if (print_verbose) {
							printf("R");
						}
						no_channels_enabled = 0;
						break;
					case 'G':
						enabled_channels.g = 1;
						if (print_verbose) {
							printf("G");
						}
						no_channels_enabled = 0;
						break;
					case 'B':
						enabled_channels.b = 1;
						if (print_verbose) {
							printf("B");
						}
						no_channels_enabled = 0;
						break;
					case 'A':
						enabled_channels.a = 1;
						if (print_verbose) {
							printf("A");
						}
						no_channels_enabled = 0;
						break;
					case 'L':
						enabled_channels.l = 1;
						if (print_verbose) {
							printf("L");
						}
						no_channels_enabled = 0;
						break;
					default:
						break;
				}
			}
			if (print_verbose) {
				if (no_channels_enabled) {
					printf("None\n");
				} else {
					printf("\n");
				}
			}
		}
	}
	return 0;
}

static int curves_process(struct PLUGIN_INDATA *in) {
	if (curves_parse_args(in->args, in->argc) != 0) {
		printerr("Failed to parse plugin args.\n");
		return PLUGIN_STATUS_ERROR;
	}

	printverb_va("Received %zu bytes of image data.\n", img_bytelen(in->src));
	if (img_realloc(in->dst, in->src->w, in->src->h) != 0) {
		return PLUGIN_STATUS_ERROR;
	}

	if (enabled_channels.r == 0 && enabled_channels.g == 0 &&
		enabled_channels.b == 0 && enabled_channels.a == 0 &&
		enabled_channels.l == 0) {
		printverb("No channels enabled. Feeding image through.\n");
		if (img_cpy(in->dst, in->src) != 0) {
			return PLUGIN_STATUS_ERROR;
		}
		return PLUGIN_STATUS_DONE;
	}

	for (unsigned int i = 0; i < img_bytelen(in->src)/RGBA_BYTES_PER_PIXEL; i++) {
		// This makes sure unaffected pixels are not modifed.
		memcpy(&in->dst->img[i], &in->src->img[i], sizeof(RGBQUAD));

		if (enabled_channels.r) {
			in->dst->img[i].rgbRed = curves_apply_function(in->src->img[i].rgbRed);
		}
		if (enabled_channels.g) {
			in->dst->img[i].rgbGreen = curves_apply_function(in->src->img[i].rgbGreen);
		}
		if (enabled_channels.b) {
			in->dst->img[i].rgbBlue = curves_apply_function(in->src->img[i].rgbBlue);
		}
		if (enabled_channels.a) {
			in->dst->img[i].rgbReserved = curves_apply_function(in->src->img[i].rgbReserved);
		}
	}

	printverb_va("Processed %zu bytes of data.\n", img_bytelen(in->src));
	return PLUGIN_STATUS_DONE;
}

static int curves_setup(void) {
	return 0;
}

static void curves_cleanup(void) {
	// Free control points array.
	if (ctrl_points) {
		free(ctrl_points);
		ctrl_points = NULL;
		num_ctrl_points = 0;
	}
}
