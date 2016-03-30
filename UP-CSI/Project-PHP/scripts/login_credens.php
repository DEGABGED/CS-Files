<?php
  //session_start();
  if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // collect value of input field
    $username = $_POST['username'];
    $userpass = $_POST['password'];
    if (empty($username) || empty($userpass)) {
      echo "<strong>Please enter a username and password.</strong>";
    } else {
      //echo "Name is ".$username."; Password is ".$userpass.".";
      //do something here with the credentials before going to home_page.php
      $GLOBALS['isPDO'] = 0;
      include 'pdo_connect.php';
      if($GLOBALS['isPDO']){
        //prepared statement
        $stmt = $db->prepare("SELECT user_pass, user_id FROM users WHERE user_name = :username;");
        $stmt->bindParam(":username", $username);
        try{
          $stmt->execute();
          //ty based w3schools
          $result = $stmt->fetch();
          if(count($result) > 1) {
            if(strcmp($result['user_pass'], $userpass) == 0){
              $_SESSION['user_id'] = $result['user_id'];
              $_SESSION['wrong_login'] = 0;
            } else {
              //echo "<br />Wrong Username/Password. Try again.";
              $_SESSION['wrong_login'] = 1;
            }
          } else if(count($result) < 1) {
            echo "<br />this shouldn't happen. wtf";
          } else {
            $_SESSION['wrong_login'] = 1;
          }
          header("Location: ".$_SERVER['REQUEST_URI']);
        } catch (PDOException $e){
          $errormsg = $e->getMessage();
          if(strlen(strchr($errormsg, "SQLSTATE[23000]")) > 0){ //hahaha
            echo "<br />Username taken. Try again.";
          } else {
            echo "<br />Something went wrong. Try again.";
          }
      } catch (Exception $e){
          $errormsg = $e->getMessage();
          header("Location: redirect.php");
        }
        exit();
      } else {
        echo "<br />ERROR occurred at login_credens. No idea what.";
      }
    }
  }
?>
