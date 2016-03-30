<?php
  $servername = '127.0.0.1';
  $user = 'root';
  $pass = 'tYVxZRj3B6cR5XPG'; //gammarayburst
  //CHANGE THE CONFIG PASSWORD!!1!!1111!!
  $dbname = 'csi-project';
  try{
    //thank you w3schools and webdevcat.com
    $db = new PDO("mysql:host=".$servername.";dbname=".$dbname, $user, $pass);
    $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    $GLOBALS['isPDO'] = 1;
  } catch (PDOException $e){
    $errormsg = $e->getMessage();
    header("Location: redirect.php");
  }
?>
