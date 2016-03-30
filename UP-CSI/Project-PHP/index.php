<?php
  //code to check for cookies
  session_start();
  if(isset($_SESSION['user_id'])){ //check for cookies
    include 'home_page.php';
  } else if(isset($_SESSION['wrong_login']) && $_SESSION['wrong_login'] == 1){
    include 'login.php';
    echo "<br />Wrong Username/Password. Try again.";
  } else {
    include 'login.php';
  }
?>
