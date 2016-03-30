<?php
  if(isset($_GET['logout']) && $_GET['logout'] == $_SESSION['user_id']){
    unset($_SESSION['user_id']);
    header("Location: index.php");
  }
?>
