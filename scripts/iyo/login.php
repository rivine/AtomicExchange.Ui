#!/usr/bin/env php
<?php
require "restapiaccess.php";

$arr = Array();
$arr["method"] = $argv[1];
$arr["cookie"] = $argv[2];
if(isset($argv[2])){
    $arr["authcode"] = $argv[3];

}

$rest = new RestApiAccess();
$sentHeaders = Array();
array_push($sentHeaders, "Cookie: ".$arr["cookie"]);

if($arr["method"] == "sms"){
    // Start 2FA procedure
    list($headers, $result) = $rest->POST("https://itsyou.online/login/smscode/main", false, $sentHeaders,json_encode($arr) );

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

    $cookie = $headers["Set-Cookie"];

    //Wait for 2FA confirmation
    while(true){

    // $cookie = $headers["Set-Cookie"];

        $sentHeaders = Array();
        array_push($sentHeaders, "Cookie: ".$cookie);
        array_push($sentHeaders, "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/65.0.3325.146 Safari/537.36");
        array_push($sentHeaders, "Origin: https://itsyou.online");
        array_push($sentHeaders, "Referer: https://itsyou.online/login");

        list($headers, $result) = $rest->GET("https://itsyou.online/login/smsconfirmed", null, $sentHeaders);
        $obj = json_decode($result);
        sleep(3);
        if($obj->confirmed){
            echo "login complete";
            exit(0);
        }
    }
}
//////////////////////


if($arr["method"] == "totp"){
    $obj = new stdClass();
    $obj->totpcode = $arr["authcode"];
    echo "posting totpconf";
    print_r(json_encode($obj));
    list($headers, $result) = $rest->POST("https://itsyou.online/login/totpconfirmation", false, $sentHeaders,json_encode($obj) );
    $returnObj = json_decode($result);

    if(isset($returnObj->redirecturl)){
        exit(0);
    }
    
    exit(1);
}