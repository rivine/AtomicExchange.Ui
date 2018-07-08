<?php
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