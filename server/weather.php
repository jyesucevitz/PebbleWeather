<?php
define('API_KEY', 'YOUR_KEY_HERE');
function get_data($url) {
    $ch = curl_init();
    $timeout = 5;
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, $timeout);
    $data = curl_exec($ch);
    curl_close($ch);
    return $data;
}
 
$payload = json_decode(file_get_contents('php://input'), true);
if(!$payload) die();
$payload[1] /= 1000000;
$payload[2] /= 1000000;
 
$contents = get_data("https://api.forecast.io/forecast/YOUR_KEY_HERE/$payload[1],$payload[2]?units=us&exclude=hourly,alerts,minutely,flags");

$forecast = json_decode($contents);
 
if(!$forecast) {
    die();
}      
$response = array();
$icons = array(
    'clear-day' => 0,
    'clear-night' => 1,
    'rain' => 2,
    'snow' => 3,
    'sleet' => 4,
    'wind' => 5,
    'fog' => 6,
    'cloudy' => 7,
    'partly-cloudy-day' => 8,
    'partly-cloudy-night' => 9
);
$sunset = $forecast->daily->data[0]->sunsetTime;
$sunset_h = date('H', $sunset);
$sunset_m =  date('m', $sunset);

$icon_id = $icons[$forecast->currently->icon];
$response[1] = array('b', $icon_id);
$response[2] = round($forecast->currently->temperature);
$response[3] = round($forecast->daily->data[0]->temperatureMax);
$response[4] = round($forecast->daily->data[0]->temperatureMin);
$response[5] = intval($sunset_h+1);
$response[6] = intval($sunset_m);

header('Content-Type: application/json');
header("Cache-Control: no-cache, must-revalidate"); // HTTP/1.1
print json_encode($response);

?>
