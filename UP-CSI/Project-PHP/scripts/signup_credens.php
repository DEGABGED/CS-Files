<?php
  session_start();
  if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // collect value of input field
    $username = $_POST['username'];
    $userpass = $_POST['password'];
    if (empty($username) || empty($userpass)) {
      echo "<strong>Please enter a username and password.</strong>";
    } else if ($userpass != $_POST['password2']) {
      echo "<strong>Password was not repeated correctly. Try again.</strong>";
    } else {
      //echo "Name is ".$username."; Password is ".$userpass.".";
      //do something here with the credentials before going to home_page.php
      $GLOBALS['isPDO'] = 0;
      include 'pdo_connect.php';
      if($GLOBALS['isPDO']){
        //prepared statement
        $stmt = $db->prepare("INSERT INTO users (user_name, user_pass)
          VALUES (:username, :userpass)");
        $stmt->bindParam(":username", $username);
        $stmt->bindParam(":userpass", $userpass);
        try{
          $stmt->execute();
          header("Location: index.php");
        } catch (PDOException $e){
          $errormsg = $e->getMessage();
          if(strlen(strchr($errormsg, "SQLSTATE[23000]")) > 0){
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
        echo "<br />ERROR occurred. No idea what.";
      }
    }
  }
?>
