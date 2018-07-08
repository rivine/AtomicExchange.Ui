#!/usr/bin/env php
<?php
require "restapiaccess.php";

$arr = Array();
$arr["login"] = $argv[1];
$arr["password"] = $argv[2];

$debug = false;

$rest = new RestApiAccess();
$headers = Array();


$sentHeaders = Array();

// POST to login to get more cookies
list($headers, $result) = $rest->POST("https://itsyou.online/login", false, $sentHeaders,json_encode($arr) );

if(substr( $headers['http_code'], 0, 10 ) === "HTTP/1.1 4"    ){
    echo "Cannot login ".$headers['http_code']."\n";
    exit(1);
}

if($debug){
    echo "Result from post to login: ".$headers['http_code']."\n";
    print_r($result);
}

$sentHeaders = Array();
$cookie = $headers["Set-Cookie"];

array_push($sentHeaders, "Cookie: ".$cookie);
array_push($sentHeaders, "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/65.0.3325.146 Safari/537.36");
array_push($sentHeaders, "Origin: https://itsyou.online");
array_push($sentHeaders, "Referer: https://itsyou.online/login");




list($headers, $result) = $rest->GET("https://itsyou.online/login/twofamethods", false, $sentHeaders );

$twofaMethods = json_decode($result);
$methods = Array();
if (isset($twofaMethods->totp)){
  array_push($methods, "totp");
}
if(isset($twofaMethods->sms)){
    array_push($methods, "sms");
}
$obj = new stdClass();
$obj->methods = $methods;
$obj->cookie = $cookie;

echo json_encode($obj);
exit(0);
