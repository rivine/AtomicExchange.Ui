#!/usr/bin/env php
<?php
require "restapiaccess.php";

$arr = Array();
$arr["cookie"] = $argv[1];
$arr["authcode"] = $argv[2];

$rest = new RestApiAccess();
$sentHeaders = Array();
array_push($sentHeaders, "Cookie: ".$arr["cookie"]);

//////////////////////


    $obj = new stdClass();
    $obj->totpcode = $arr["authcode"];

    print_r(json_encode($obj));
    list($headers, $result) = $rest->POST("https://itsyou.online/login/totpconfirmation", false, $sentHeaders,json_encode($obj) );
    $returnObj = json_decode($result);

    if(isset($returnObj->redirecturl)){
        exit(0);
    }
    
    exit(1);
