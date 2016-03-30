<?php
	if ($_SERVER["REQUEST_METHOD"] == "GET" && isset($_GET['search'])){
		//get search term
		$searchterm = $_GET['search'];
		//$GLOBALS['isPDO'] = 0;
		//include 'pdo_connect.php';
		if(isset($GLOBALS['isPDO']) && $GLOBALS['isPDO']){
			//prepared statement
			$stmt3 = $db->prepare("SELECT group_id FROM groups WHERE group_name = :search;");
			$stmt3->bindParam(":search", $searchterm);
			try{
				$stmt3->execute();
				//ty based w3schools
				$result = $stmt3->fetch();
				if(count($result) > 1) { //get the events and shit
					$group = getGroupName($result['group_id']);
					echo '<h4>'.$group.'</h4>';
					echo '<div class="btn-group">';
					if(!isGroupFollowed($result['group_id'])){
						echo '<a href='.$_SERVER["PHP_SELF"].'?group_follow='.$result['group_id'].'><input type="button" class="btn btn-default" value="Follow Group"></a>';
					} else {
						$auth = isUserAuthorized($_SESSION['user_id'], $result['group_id']);
						if($auth >= 1){
							echo '<a href=settings_page.php?request=1&group_id='.$result['group_id'].'><input type="button" class="btn btn-default" value="Add Event"></a>&nbsp';
							echo '<a href=settings_page.php?request=2&group_id='.$result['group_id'].'><input type="button" class="btn btn-default" value="Delete Event"></a>&nbsp';
						}
						if($auth >= 3){
							echo '<a href=settings_page.php?request=3&group_id='.$result['group_id'].'><input type="button" class="btn btn-default" value="Add Admin"></a>&nbsp';
							echo '<a href=settings_page.php?request=4&group_id='.$result['group_id'].'><input type="button" class="btn btn-default" value="Delete Admin"></a>&nbsp';
							echo '<a href='.$_SERVER["PHP_SELF"].'?group_delete='.$result['group_id'].'><input type="button" class="btn btn-danger" value="Delete Group"></a>';
						} else {
							echo '<a href='.$_SERVER["PHP_SELF"].'?group_unfollow='.$result['group_id'].'><input type="button" class="btn btn-danger" value="Unfollow Group"></a>';
						}
					}

					echo '</div>';
					$stmt3 = $db->prepare("SELECT event_id FROM group_events WHERE group_id = :group;");
					$stmt3->bindParam(":group", $result['group_id']);
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
				} else {
					echo "<br />No such group. Try again.";
				}
			} catch (PDOException $e){
		      $errormsg = $e->getMessage();
		      header("Location: redirect.php");
		    }
		} else {
			echo "<br />ERROR occurred at search_bar. No idea what.";
		}
	}
?>
