#include "plugin.h"
#include "imgutil/imgutil.h"

static int curves_process(const IMAGE *img, IMAGE *img_dest,
				const char **plugin_args,
				const unsigned int plugin_args_count);
static int curves_setup(void);
static void curves_cleanup(void);

PLUGIN_INFO PLUGIN_INFO_NAME(curves) = {
	.name = "curves",
	.descr = "A curve based image manipulation plugin.",
	.author = "Eero Talus",
	.year = "2017",

	.valid_args = NULL,
	.valid_args_count = 0,

	.plugin_process = &curves_process,
	.plugin_setup = &curves_setup,
	.plugin_cleanup = &curves_cleanup
};

static int curves_process(const IMAGE *img, IMAGE *img_dest,
				const char **plugin_args,
				const unsigned int plugin_args_count) {

	return 0;
}

static int curves_setup(void) {
	return 0;
}

static void curves_cleanup(void) {

}
