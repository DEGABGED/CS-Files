<?php
  //session_start();
  //reset session group variable
  if(isset($_SESSION['group_followed'])) unset($_SESSION['group_followed']); //it's gonna be reset in the sidebar.php anyway
  if(isset($_GET['group_follow']) && isGroupFollowed($_GET['group_follow']) == 0){
    try{
      $stmtf = $db->prepare("INSERT INTO group_users (group_id, user_id)
        VALUES (:group, :user);");
      $stmtf->bindParam(":group", $_GET['group_follow']);
      $stmtf->bindParam(":user", $_SESSION['user_id']);
      $stmtf->execute();
    } catch (PDOException $e){
      $errormsg = $e->getMessage();
      header("Location: redirect.php");
    }
  } else if(isset($_GET['group_unfollow']) && isGroupFollowed($_GET['group_unfollow']) == 1){
    try{
      $stmtf = $db->prepare("DELETE FROM group_auth WHERE group_id = :group && authuser_id = :user;");
      $stmtf->bindParam(":group", $_GET['group_unfollow']);
      $stmtf->bindParam(":user", $_SESSION['user_id']);
      $stmtf->execute();
      $stmtf = $db->prepare("DELETE FROM group_users WHERE group_id = :group && user_id = :user;");
      $stmtf->bindParam(":group", $_GET['group_unfollow']);
      $stmtf->bindParam(":user", $_SESSION['user_id']);
      $stmtf->execute();
    } catch (PDOException $e){
      $errormsg = $e->getMessage();
      header("Location: redirect.php");
    }
  } else if(isset($_GET['group_delete']) && isUserAuthorized($_SESSION['user_id'], $_GET['group_delete']) >= 3){
      try{
        $stmtf = $db->prepare("DELETE FROM group_auth WHERE group_id = :group;");
        $stmtf->bindParam(":group", $_GET['group_delete']);
        $stmtf->execute();
        $stmtf = $db->prepare("DELETE FROM group_users WHERE group_id = :group;");
        $stmtf->bindParam(":group", $_GET['group_delete']);
        $stmtf->execute();
        /*
        $stmtf = $db->prepare("DELETE FROM group_events WHERE group_id = :group;"); //this will leave hanging events, but is useful when multi group events are introduced
        $stmtf->bindParam(":group", $_GET['group_delete']);
        $stmtf->execute();
        */
        $stmt = $db->prepare("SELECT event_id FROM group_events WHERE group_id = :group;");
        $stmt->bindParam(":group", $_GET['group_delete']);
        $stmt->execute();
        $result = $stmt->fetch();
        while($result['event_id']){
            $stmtf = $db->prepare("DELETE FROM group_events WHERE group_id = :group AND event_id = :event;");
            $stmtf->bindParam(":group", $_GET['group_delete']);
            $stmtf->bindParam(":event", $result['event_id']);
            $stmtf->execute();

            $stmtf = $db->prepare("DELETE FROM events WHERE event_id = :event;");
            $stmtf->bindParam(":event", $result['event_id']);
            try{
                $stmtf->execute();
            } catch (PDOException $e) {}
            $result = $stmt->fetch();
        }

        $stmtf = $db->prepare("DELETE FROM groups WHERE group_id = :group;");
        $stmtf->bindParam(":group", $_GET['group_delete']);
        $stmtf->execute();
      } catch (PDOException $e){
        $errormsg = $e->getMessage();
        header("Location: redirect.php");
      }
  }
?>
