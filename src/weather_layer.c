#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"
#include "util.h"
#include "weather_layer.h"
#include "config.h"
//left,
#define WEATHER_ICON_FRAME  (GRect(14, 8, 50, 50))
#define WEATHER_TEMP_FRAME  (GRect(65, 5, 65, 50))
#define WEATHER_SUNSET_FRAME  (GRect(0, 74, 144, 15))
#define WEATHER_HL_FRAME    (GRect(0, 57, 144, 30))

static uint8_t WEATHER_ICONS[] = {
	RESOURCE_ID_ICON_CLEAR_DAY,
	RESOURCE_ID_ICON_CLEAR_NIGHT,
	RESOURCE_ID_ICON_RAIN,
	RESOURCE_ID_ICON_SNOW,
	RESOURCE_ID_ICON_SLEET,
	RESOURCE_ID_ICON_WIND,
	RESOURCE_ID_ICON_FOG,
	RESOURCE_ID_ICON_CLOUDY,
	RESOURCE_ID_ICON_PARTLY_CLOUDY_DAY,
	RESOURCE_ID_ICON_PARTLY_CLOUDY_NIGHT,
	RESOURCE_ID_ICON_ERROR,
};

void weather_layer_init(WeatherLayer* weather_layer) {
	layer_init(&weather_layer->layer, GRect(0, 0, 144, 168));
	
/*
TEMP FRAME
******************************/
	text_layer_init(&weather_layer->temp_layer, WEATHER_TEMP_FRAME);
	text_layer_set_background_color(&weather_layer->temp_layer, GColorClear);
  text_layer_set_text_color(&weather_layer->temp_layer, COLOUR_TEXT_TOP_SPLIT);
	text_layer_set_text_alignment(&weather_layer->temp_layer, GTextAlignmentCenter);
  text_layer_set_font(&weather_layer->temp_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_MEDIUM_45)));
	layer_add_child(&weather_layer->layer, &weather_layer->temp_layer.layer);

/*
HIGH / LOW FRAME
******************************/
	text_layer_init(&weather_layer->temp_layer_highlow, WEATHER_HL_FRAME);
	text_layer_set_background_color(&weather_layer->temp_layer_highlow, GColorClear);
  text_layer_set_text_color(&weather_layer->temp_layer_highlow, COLOUR_TEXT_TOP_SPLIT);
	text_layer_set_text_alignment(&weather_layer->temp_layer_highlow, GTextAlignmentCenter);
	text_layer_set_font(&weather_layer->temp_layer_highlow, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_SMALL_14)));
	layer_add_child(&weather_layer->layer, &weather_layer->temp_layer_highlow.layer);
	
/*
SUNSET FRAME
******************************/
	text_layer_init(&weather_layer->temp_layer_sunset, WEATHER_SUNSET_FRAME);
	text_layer_set_background_color(&weather_layer->temp_layer_sunset, GColorBlack);
  text_layer_set_text_color(&weather_layer->temp_layer_sunset, GColorWhite);
	text_layer_set_text_alignment(&weather_layer->temp_layer_sunset, GTextAlignmentCenter);
	text_layer_set_font(&weather_layer->temp_layer_sunset, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_SMALL_14)));
	layer_add_child(&weather_layer->layer, &weather_layer->temp_layer_sunset.layer);
	
	// Note absence of icon layer
	weather_layer->has_weather_icon = false;
}


/*
ICON LAYER
******************************/
void weather_layer_set_icon(WeatherLayer* weather_layer, WeatherIcon icon) {	
	// Remove any possible existing weather icon
	if(weather_layer->has_weather_icon) {
		layer_remove_from_parent(&weather_layer->icon_layer.layer.layer);
		bmp_deinit_container(&weather_layer->icon_layer);
		weather_layer->has_weather_icon = false;
	}
	
	bmp_init_container(WEATHER_ICONS[icon], &weather_layer->icon_layer);
	layer_add_child(&weather_layer->layer, &weather_layer->icon_layer.layer.layer);
	layer_set_frame(&weather_layer->icon_layer.layer.layer, WEATHER_ICON_FRAME);
	weather_layer->has_weather_icon = true;
}
/*
HIGH / LOW LAYE
******************************/
void weather_layer_set_highlow(WeatherLayer* weather_layer, int16_t high, int16_t low) {
  snprintf(weather_layer->highlow, sizeof(weather_layer->highlow), "LOW: %d°  HIGH: %d°", low, high);
  text_layer_set_text(&weather_layer->temp_layer_highlow, weather_layer->highlow);
}
/*
TEMP LAYER
******************************/
void weather_layer_set_temperature(WeatherLayer* weather_layer, int16_t t) {
  snprintf(weather_layer->temperature, sizeof(weather_layer->temperature), "%d°", t);
	text_layer_set_text(&weather_layer->temp_layer, weather_layer->temperature);  
}
/*
SUNSET Layer
******************************/
void weather_layer_set_sunset(WeatherLayer* weather_layer, int16_t sunset_h, int16_t sunset_m) {
  snprintf(weather_layer->sunsettime, sizeof(weather_layer->sunsettime), "SUNSET : %d:%02d", sunset_h, sunset_m);
	text_layer_set_text(&weather_layer->temp_layer_sunset, weather_layer->sunsettime);  
}
/*
******************************/
void weather_layer_set_error(WeatherLayer* weather_layer, int http_status) {
	weather_layer_set_icon(weather_layer, WEATHER_ICON_NO_WEATHER);
  snprintf(weather_layer->temperature, sizeof(weather_layer->temperature), "%d", http_status);
	text_layer_set_text(&weather_layer->temp_layer, weather_layer->temperature);  
}

void weather_layer_deinit(WeatherLayer* weather_layer) {
	if(weather_layer->has_weather_icon)
		bmp_deinit_container(&weather_layer->icon_layer);
}
