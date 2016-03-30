<!-- TODO: Put account settings here -->
<div id="sidebar-wrapper">
<h3><?php echo getUserName($_SESSION['user_id'])?></h3>
<a href='index.php'><button type="button" class="btn btn-default">Home</button></a>
<a href='settings_page.php'><button type="button" class="btn btn-default">Settings</button></a><br /><br />
<a href=<?php echo 'index.php?logout='.$_SESSION['user_id'] ?>><button type="button" class="btn btn-danger">Log Out</button></a><br />
<br />
<form role="search" action="index.php" method="get">
  <div class="form-group">
    Follow groups : <br/><input type="text" name="search" id="search_term"><br />
  </div>
  <button type="submit" class="btn btn-default">Submit</button>
</form>
<br />
<ul class="nav nav-pills nav-stacked">
<!-- display groups it joined -->
<?php
  //$GLOBALS['isPDO'] = 0;
  //include 'pdo_connect.php';
  if(isset($GLOBALS['isPDO']) && $GLOBALS['isPDO']){
    try{
      //prepared statement: Find group_id of followed groups
      $stmt = $db->prepare("SELECT group_id FROM group_users WHERE user_id = :user;");
      $stmt->bindParam(":user", $_SESSION['user_id']);
      $stmt->execute();
      $result = $stmt->fetch();
      //get the groups
      if(count($result) > 1) {
        //TODO: Store followed groups in a superglobal array
        $_SESSION['group_followed'] = $result['group_id']; //'group_followed' being set means that at least one group is being followed
        while($result['group_id']){
          //prepared statement: Find group name from group_id
          //$stmt2 = $db->prepare("SELECT group_name FROM groups WHERE group_id = :group;");
          //$stmt2->bindParam(":group", $result['group_id']);
          //$stmt2->execute();
          $group = getGroupName($result['group_id']);
          echo "<li><a href=index.php?group_id=".$result['group_id'].">".$group."</a></li>";

          $result = $stmt->fetch();
        }
      } else {
        echo "<br />Try joining some groups!";
      }
    } catch (PDOException $e){
      $errormsg = $e->getMessage();
      header("Location: redirect.php");
    }
  } else {
    echo "<br />ERROR occurred at sidebar. No idea what.";
  }
?>
</ul>
</div>
