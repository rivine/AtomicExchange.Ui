<?php

require "restapiaccess.php";
$debug = false;
$arr = Array();
$arr["cookie"] = $argv[1];

$rest = new RestApiAccess();
$sentHeaders = Array();
array_push($sentHeaders, "Cookie: ".$arr["cookie"]);


// Start 2FA procedure
list($headers, $result) = $rest->POST("https://itsyou.online/login/smscode/main", false, $sentHeaders,json_encode($arr) );


$cookie = $headers["Set-Cookie"];

if(substr( $headers['http_code'], 0, 10 ) === "HTTP/1.1 4"    ){
    echo "Getting 2FA SMS failed: ".$headers['http_code'];
    exit(1);
}

if($debug){
    echo "Result from post to sms: ".$headers['http_code'];
}


if($headers["http_code"] == "HTTP/1.1 429 Too Many Requests"){
    echo "Too many requests";
    exit(1);
}
echo $cookie;

