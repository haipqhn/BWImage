#include <jni.h>
#include <android/log.h>
#include <android/bitmap.h>

#define  LOG_TAG    "loggrayscale"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

typedef struct {
	uint8_t alpha;
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} argb;
JNIEXPORT void JNICALL Java_vn_haipq_bwimage_BWImage_convertToGrayscale (JNIEnv * env, jobject obj, jobject bitmapcolor,jobject bitmapgray)
{
	AndroidBitmapInfo infocolor;
	void* pixelscolor;
	AndroidBitmapInfo infogray;
	void* pixelsgray;
	int ret;
	int y;
	int x;

	LOGI("convertToGray");
	if ((ret = AndroidBitmap_getInfo(env, bitmapcolor, &infocolor)) < 0) {
		LOGE("AndroidBitmap_getInfo() failed ! error=%d", ret);
		return;
	}

	if ((ret = AndroidBitmap_getInfo(env, bitmapgray, &infogray)) < 0) {
		LOGE("AndroidBitmap_getInfo() failed ! error=%d", ret);
		return;
	}

	LOGI("color image :: width is %d; height is %d; stride is %d; format is %d;flags is %d", infocolor.width, infocolor.height, infocolor.stride, infocolor.format, infocolor.flags);
	if (infocolor.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
		LOGE("Bitmap format is not RGBA_8888 !");
		return;
	}

	LOGI(
			"gray image :: width is %d; height is %d; stride is %d; format is %d;flags is %d", infogray.width, infogray.height, infogray.stride, infogray.format, infogray.flags);
	if (infogray.format != ANDROID_BITMAP_FORMAT_A_8) {
		LOGE("Bitmap format is not A_8 !");
		return;
	}

	if ((ret = AndroidBitmap_lockPixels(env, bitmapcolor, &pixelscolor)) < 0) {
		LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
	}

	if ((ret = AndroidBitmap_lockPixels(env, bitmapgray, &pixelsgray)) < 0) {
		LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
	}

	// modify pixels with image processing algorithm

	for (y=0;y<infocolor.height;y++) {
		argb * line = (argb *) pixelscolor;
		uint8_t * grayline = (uint8_t *) pixelsgray;
		for (x=0;x<infocolor.width;x++) {
			grayline[x] = 255 - (line[x].red + line[x].green + line[x].blue)/3;
		}

		pixelscolor = (char *)pixelscolor + infocolor.stride;
		pixelsgray = (char *) pixelsgray + infogray.stride;
	}

	LOGI("unlocking pixels");
	AndroidBitmap_unlockPixels(env, bitmapcolor);
	AndroidBitmap_unlockPixels(env, bitmapgray);

}
