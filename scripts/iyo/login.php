#!/usr/bin/env php
<?php

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

//////////////////////


class RestApiAccess {
    


    public function GET($url, $data = false, $headers = array(), $jsonData = false){
         return $this->CallApi("GET", $url, $data, $headers, $jsonData);
     }
     
    public function POST($url, $data = false, $headers = array(), $jsonData = false){
    
        return $this->CallApi("POST", $url, $data, $headers, $jsonData);
     }
     
     public function PUT($url, $data = false, $headers = array(), $jsonData = false) {
        return $this->CallApi("PUT", $url, $data, $headers, $jsonData);
     }
     public function DELETE($url, $data = false, $headers = array(), $jsonData = false) {
        return $this->CallApi("DELETE", $url, $data, $headers, $jsonData);
     }
     
     public function GetHeaders($response)
 {
     $headers = array();
 
     $header_text = substr($response, 0, strpos($response, "\r\n\r\n"));
 
     foreach (explode("\r\n", $header_text) as $i => $line)
         if ($i === 0)
             $headers['http_code'] = $line;
         else
         {
             list ($key, $value) = explode(': ', $line);
             if($key == "Set-Cookie"){ //should not be here
                 if(strpos($value, ";")){
                     $value = substr($value, 0, strpos($value, ";"));
                 }
             }
             if(isset($headers[$key])){
 
                
                 $headers[$key] =  $headers[$key]."; ".$value;
 
             }else{
                 $headers[$key] = $value;
             }
             
         }
 
     return $headers;
 }
     
     // Method: POST, PUT, GET etc
 // Data: array("param" => "value") ==> index.php?param=value
 
    public function CallAPI($method, $url, $data = false, $headers, $jsonData = false)
     {
         $curl = curl_init();
         curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, false); //@todo only for testing!!
 //curl_setopt($curl, CURLOPT_VERBOSE, TRUE);
         if($jsonData) {
             array_push($headers,"Content-Type: application/json");
             curl_setopt($curl, CURLOPT_POSTFIELDS,$jsonData);
         }
         curl_setopt($curl, CURLOPT_HTTPHEADER, $headers);
 
         switch ($method)
         {
             case "POST":
            
                 curl_setopt($curl, CURLOPT_POST, 1);
                 if(!$jsonData && !$data){
                      curl_setopt($curl, CURLOPT_POSTFIELDS,null);
                 }
                if ($data){
 
 
                     curl_setopt($curl, CURLOPT_POSTFIELDS, $data);
                     }
                     break;
 
             case "PUT":
                 curl_setopt($curl, CURLOPT_CUSTOMREQUEST, "PUT");
                 if ($data)
                     curl_setopt($curl, CURLOPT_POSTFIELDS, $data);
 
                 break;
             case "DELETE":
                 curl_setopt($curl, CURLOPT_CUSTOMREQUEST, "DELETE");
                 break; 
             default:
 
                 if ($data)
                     $url = sprintf("%s?%s", $url, http_build_query($data));
         }
 
         // Optional Authentication:
        /* curl_setopt($curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
         curl_setopt($curl, CURLOPT_USERPWD, "username:password");
 */
         curl_setopt($curl, CURLOPT_URL, $url);
         curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
 
         curl_setopt($curl, CURLOPT_HEADER, true);
         $response = curl_exec($curl); 
         $headers = $this->GetHeaders($response);
      
         $header_size = curl_getinfo($curl, CURLINFO_HEADER_SIZE);
         $response = substr($response, $header_size);
 
 //        $result = curl_exec($curl);
         $httpcode = curl_getinfo($curl, CURLINFO_HTTP_CODE);
 
         
 
         curl_close($curl);
   
 
         return array($headers, $response);
     }
 
 }