<?php

require "restapiaccess.php";

$arr = Array();
$arr["cookie"] = $argv[1];

$rest = new RestApiAccess();


//Wait for 2FA confirmation
while(true){

// $cookie = $headers["Set-Cookie"];

   // $sentHeaders = Array();
   $sentHeaders = Array();
   array_push($sentHeaders, "Cookie: ".$arr["cookie"]);
   
    array_push($sentHeaders, "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/65.0.3325.146 Safari/537.36");
    array_push($sentHeaders, "Origin: https://itsyou.online");
    array_push($sentHeaders, "Referer: https://itsyou.online/login");

    list($headers, $result) = $rest->GET("https://itsyou.online/login/smsconfirmed", null, $sentHeaders);
   // print_r($headers);

    $cookie2 = $headers["Set-Cookie"];
  //  echo $cookie2;
    $obj = json_decode($result);
    sleep(3);
    if($obj->confirmed){
        echo "login complete";
        exit(0);
    }
}
