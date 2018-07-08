#!/usr/bin/env php
<?php
require "restapiaccess.php";

$arr = Array();
$arr["cookie"] = $argv[1];
$arr["smscode"] = $argv[2];

$rest = new RestApiAccess();
$sentHeaders = Array();
array_push($sentHeaders, "Cookie: ".$arr["cookie"]);

//////////////////////
$obj = new stdClass();
$obj->smscode = $arr["smscode"];

list($headers, $result) = $rest->POST("https://itsyou.online/login/smsconfirmation", false, $sentHeaders,json_encode($obj) );
//poll once for login session id
$returnObj = json_decode($result);

if(isset($returnObj->redirecturl)){
    exit(0);
}

exit(1);