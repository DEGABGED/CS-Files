<?php
	if(isset($_GET['search'])){ //run if a search query is found
		//do nothing; search_bar already does this
	} else if(isset($_GET['group_follow']) || isset($_GET['group_unfollow'])){ //run if a follow button is clicked; toggle
		//display the group un/followed, but w/ change of button
		//$GLOBALS['isPDO'] = 0;
		//include 'pdo_connect.php';
		if(isset($GLOBALS['isPDO']) && $GLOBALS['isPDO']){
			//prepared statement
			try{
					//follow/unfollow group option
					//At this point, the follow/unfollow is reflected in the database. Hopefully.
					$group_display = isset($_GET['group_follow']) ? $_GET['group_follow'] : $_GET['group_unfollow'];
					$group = getGroupName($group_display);
					echo '<h4>'.$group.'</h4>';
					echo '<div class="btn-group">';
					$auth = isUserAuthorized($_SESSION['user_id'], $group_display); //you never know
					if($auth >= 1){
						echo '<a href=settings_page.php?request=1&group_id='.$group_display.'><input type="button" class="btn btn-default" value="Add Event"></a>&nbsp';
						echo '<a href=settings_page.php?request=2&group_id='.$group_display.'><input type="button" class="btn btn-default" value="Delete Event"></a>&nbsp';
					}
					if($auth >= 3){
						echo '<a href=settings_page.php?request=3&group_id='.$group_display.'><input type="button" class="btn btn-default" value="Add Admin"></a>&nbsp';
						echo '<a href=settings_page.php?request=4&group_id='.$group_display.'><input type="button" class="btn btn-default" value="Delete Admin"></a>&nbsp';
					}
					if(isset($_GET['group_follow'])){
						echo '<a href='.$_SERVER["PHP_SELF"].'?group_unfollow='
							.$_GET['group_follow'].'><input type="button" class="btn btn-danger" value="Unfollow Group"></a>';
					} else if(isset($_GET['group_unfollow'])){
							echo '<a href='.$_SERVER["PHP_SELF"].'?group_follow='
								.$_GET['group_unfollow'].'><input type="button" class="btn btn-default" value="Follow Group"></a>';
					}
					echo '</div>';
					$stmt3 = $db->prepare("SELECT event_id FROM group_events WHERE group_id = :group;");
					$stmt3->bindParam(":group", $group_display);
					$stmt3->execute();
					$result = $stmt3->fetch();
					echo '<div class="list-group">';
					while($result['event_id']){
						//get event data from the event id
						$stmt4 = $db->prepare("SELECT event_name, event_date, event_time, event_venue, event_desc FROM events WHERE event_id = :search;");
						$stmt4->bindParam(":search", $result['event_id']);
						$stmt4->execute();
						$event = $stmt4->fetch();
						displayEvent($event);
						$result = $stmt3->fetch();
					}
					echo '</div>';
			} catch (PDOException $e){
		      $errormsg = $e->getMessage();
		      header("Location: redirect.php");
		    }
		} else {
			echo "<br />ERROR occurred at display_events. No idea what.";
		}
	} else if(isset($_SESSION['group_followed']) || isset($_GET['group_id'])){ //home page w/ group followed or group click
		//generate from followed event
    	//$GLOBALS['isPDO'] = 0;
		//include 'pdo_connect.php';
		if(isset($GLOBALS['isPDO']) && $GLOBALS['isPDO']){
			//prepared statement
			try{
					//follow/unfollow group option
					$group_display = isset($_GET['group_id']) ? $_GET['group_id'] : $_SESSION['group_followed'];
					$group = getGroupName($group_display);
					echo '<h4>'.$group.'</h4>';
					echo '<div class="btn-group">';
					$auth = isUserAuthorized($_SESSION['user_id'], $group_display);
					if($auth >= 1){
						echo '<a href=settings_page.php?request=1&group_id='.$group_display.'><input type="button" class="btn btn-default" value="Add Event"></a>&nbsp';
						echo '<a href=settings_page.php?request=2&group_id='.$group_display.'><input type="button" class="btn btn-default" value="Delete Event"></a>&nbsp';
					}
					if($auth >= 3){
						echo '<a href=settings_page.php?request=3&group_id='.$group_display.'><input type="button" class="btn btn-default" value="Add Admin"></a>&nbsp';
						echo '<a href=settings_page.php?request=4&group_id='.$group_display.'><input type="button" class="btn btn-default" value="Delete Admin"></a>&nbsp';
						echo '<a href='.$_SERVER["PHP_SELF"].'?group_delete='.$group_display.'><input type="button" class="btn btn-danger" value="Delete Group"></a>';
					} else {
						echo '<a href='.$_SERVER["PHP_SELF"].'?group_unfollow='.$group_display.'><input type="button" class="btn btn-danger" value="Unfollow Group"></a>';
					}
					echo '</div>';
					$stmt3 = $db->prepare("SELECT event_id FROM group_events WHERE group_id = :group;");
					$stmt3->bindParam(":group", $group_display);
					$stmt3->execute();
					$result = $stmt3->fetch();
					while($result['event_id']){
						//get event data from the event id
						$stmt4 = $db->prepare("SELECT event_name, event_date, event_time, event_venue, event_desc FROM events WHERE event_id = :search;");
						$stmt4->bindParam(":search", $result['event_id']);
						$stmt4->execute();
						$event = $stmt4->fetch();
						displayEvent($event);
						$result = $stmt3->fetch();
					}
			} catch (PDOException $e){
		      $errormsg = $e->getMessage();
		      header("Location: redirect.php");
		    }
		} else {
			echo "<br />ERROR occurred at display_events. No idea what.";
		}
	} else { //home page w/ no group followed
		echo "<br /> Currently displaying no events.";
	}
?>
