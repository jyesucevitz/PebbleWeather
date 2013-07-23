#define SERVER_URL "http://futtle.com/pebble/yahoo-weather.php"

//1=ON;0=OFF - loads appropriate background image
#define SPLIT_MODE 1

//USE DIFFERENT COLOURS FOR TOP/BOTTOM OFF THE SCREEN
#define COLOUR_TEXT_TOP_SPLIT GColorBlack
#define COLOUR_TEXT_BOTTOM_SPLIT GColorWhite

//Celsius / Fahrenheit
#define UNIT_SYSTEM "f" // c or f

//Check for new weather every X minutes (server code has 14 minute cache header)
#define FREQUENCY_MINUTES 15

// POST variables
#define WEATHER_KEY_LATITUDE 1
#define WEATHER_KEY_LONGITUDE 2
#define WEATHER_KEY_UNIT_SYSTEM 3
	
// Received variables
#define WEATHER_KEY_ICON 1
#define WEATHER_KEY_TEMPERATURE 2
#define WEATHER_KEY_HIGH 3
#define WEATHER_KEY_LOW 4

#define WEATHER_HTTP_COOKIE 1949999771
#define TIME_HTTP_COOKIE 1199938782

