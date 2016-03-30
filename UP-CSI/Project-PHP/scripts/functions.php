<?php
  function displayEvent($event){
    echo '<button type="button" class="list-group-item">';
    echo "<p><br /><strong>".$event['event_name']."</strong><br />";
    echo "Date: ".date('F d, Y', strtotime($event['event_date'])).", Time: ".$event['event_time']."<br />";
    echo "Venue: ".$event['event_venue']."<br />";
    echo "Description: ".$event['event_desc']."</p><br />";
    echo "</button>";
  }

  function isGroupFollowed($group){
    try{
      //prepared statement: Find group_id of followed groups
      include 'pdo_connect.php';
      $stmt = $db->prepare("SELECT group_id FROM group_users WHERE user_id = :user;");
      $stmt->bindParam(":user", $_SESSION['user_id']);
      $stmt->execute();
      $result = $stmt->fetch();
      //get the groups
      if(count($result) > 1) {
        $_SESSION['group_followed'] = $result['group_id']; //'group_followed' being set means that at least one group is being followed
        while($result['group_id']){
          if($result['group_id'] == $group){
            return 1;
          }
          $result = $stmt->fetch();
        }
      }
    } catch (PDOException $e){
      $errormsg = $e->getMessage();
      return -1;
    }
    return 0;
  }

  function getGroupName($group){
    try{
      //prepared statement: Find group_id of followed groups
      include 'pdo_connect.php';
      $stmt = $db->prepare("SELECT group_name FROM groups WHERE group_id = :group;");
      $stmt->bindParam(":group", $group);
      $stmt->execute();
      $result = $stmt->fetch();
      //get the group name
      if(isset($result['group_name'])){
        return $result['group_name'];
      }
    } catch (PDOException $e){
      $errormsg = $e->getMessage();
      return -1;
    }
    return 0;
  }

  function getGroupId($group_name){
      try{
        //prepared statement: Find group_id of followed groups
        include 'pdo_connect.php';
        $stmt = $db->prepare("SELECT group_id FROM groups WHERE group_name = :group;");
        $stmt->bindParam(":group", $group_name);
        $stmt->execute();
        $result = $stmt->fetch();
        //get the group name
        if(isset($result['group_id'])){
          return $result['group_id'];
        }
      } catch (PDOException $e){
        $errormsg = $e->getMessage();
        echo $errormsg;
        return -1;
      }
      return 0;
  }

  function getGroupCreator($group){
    try{
      //prepared statement: Find group_id of followed groups
      include 'pdo_connect.php';
      $stmt = $db->prepare("SELECT group_creator FROM groups WHERE group_id = :group;");
      $stmt->bindParam(":group", $group);
      $stmt->execute();
      $result = $stmt->fetch();
      //get the group name
      if(isset($result['group_creator'])){
        return $result['group_creator'];
      }
    } catch (PDOException $e){
      $errormsg = $e->getMessage();
      return -1;
    }
    return 0;
  }

  function getUserId($user_name){
    try{
      //prepared statement: Find group_id of followed groups
      include 'pdo_connect.php';
      $stmt = $db->prepare("SELECT user_id FROM users WHERE user_name = :user;");
      $stmt->bindParam(":user", $user_name);
      $stmt->execute();
      $result = $stmt->fetch();
      //get the group name
      if(isset($result['user_id'])){
        return $result['user_id'];
      }
    } catch (PDOException $e){
      $errormsg = $e->getMessage();
      echo $errormsg;
      return -1;
    }
    return 0;
  }

  function getUserName($user_id){
    try{
      //prepared statement: Find group_id of followed groups
      include 'pdo_connect.php';
      $stmt = $db->prepare("SELECT user_name FROM users WHERE user_id = :user;");
      $stmt->bindParam(":user", $user_id);
      $stmt->execute();
      $result = $stmt->fetch();
      //get the group name
      if(isset($result['user_name'])){
        return $result['user_name'];
      }
    } catch (PDOException $e){
      $errormsg = $e->getMessage();
      echo $errormsg;
      return -1;
    }
    return 0;
  }

  function isUserAuthorized($user_id, $group){ //$action - 1: adding events, 2: authorizing people for 1
      try{
          include 'pdo_connect.php';
          $stmt = $db->prepare("SELECT group_creator FROM groups WHERE group_id = :group;");
          $stmt->bindParam(":group", $group);
          $stmt->execute();
          $result = $stmt->fetch();
          if($result['group_creator'] == $user_id){
              //the creator of a group has all rights
              return 4;
          } else {
              $stmt = $db->prepare("SELECT authuser_id FROM group_auth WHERE group_id = :group;");
              $stmt->bindParam(":group", $group);
              $stmt->execute();
              $result2 = $stmt->fetch();
              if(isset($result2['authuser_id'])){
                  while($result2['authuser_id']){
                      if($result2['authuser_id'] == $user_id) return 2;
                      $result2 = $stmt->fetch();
                  }
              }
          }
      } catch (PDOException $e){
        $errormsg = $e->getMessage();
        echo $errormsg;
        return -1;
      }
      return 0;

      //-1: error; 0: no auth; 2: add events; 4: auth users
  }

  function isUserFollowing($user_id, $group){
      try{
          include 'pdo_connect.php';
          $stmt = $db->prepare("SELECT group_id FROM group_users WHERE user_id = :user;");
          $stmt->bindParam(":user", $user_id);
          $stmt->execute();
          $result = $stmt->fetch();
          while($result['group_id']){
              if($result['group_id'] == $group) return 1;
              $result = $stmt->fetch();
          }
          return 0;
      } catch (PDOException $e){
        $errormsg = $e->getMessage();
        echo $errormsg;
        return -1;
      }
  }

  function doesGroupExist($group_name){
      try{
          include 'pdo_connect.php';
          $stmt = $db->prepare("SELECT group_id FROM groups WHERE group_name = :group;");
          $stmt->bindParam(":group", $group_name);
          $stmt->execute();
          $result = $stmt->fetch();
          if(isset($result['group_id'])) return 1;
          else return 0;
      } catch (PDOException $e){
        $errormsg = $e->getMessage();
        echo $errormsg;
        return -1;
      }
  }
?>
