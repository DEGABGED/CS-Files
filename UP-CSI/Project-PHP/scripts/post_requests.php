<?php
    if ($_SERVER["REQUEST_METHOD"] == "POST"){
        if(isset($_GET['request']) && isset($_GET['group_id'])){
            if($_GET['request'] == 1){ //add event
                try{
                    $stmt = $db->prepare("INSERT INTO events
                      (event_name, event_date, event_time, event_venue, event_desc, event_creator)
                      VALUES (:event_name, :event_date, :event_time, :event_venue, :event_desc, :event_creator)");
                    $stmt->bindParam(":event_name", $_POST['event_name']);
                    $stmt->bindParam(":event_date", $_POST['event_date']);
                    $stmt->bindParam(":event_time", $_POST['event_time']);
                    $stmt->bindParam(":event_venue", $_POST['event_venue']);
                    $stmt->bindParam(":event_desc", $_POST['event_desc']);
                    $stmt->bindParam(":event_creator", $_SESSION['user_id']);
                    $stmt->execute();

                    $stmt = $db->prepare("SELECT event_id FROM events WHERE event_name = :event_name");
                    $stmt->bindParam(":event_name", $_POST['event_name']);
                    $stmt->execute();
                    $result = $stmt->fetch();
                    $result_id = 0;
                    while($result['event_id']){ //in case multiple w/ the same name was made. No idea if event name is unique
                        $result_id = $result['event_id'];
                        $result = $stmt->fetch();
                    }

                    $stmt = $db->prepare("INSERT INTO group_events
                      (event_id, group_id) VALUES (:event_id, :group_id)");
                    $stmt->bindParam(":event_id", $result_id);
                    $stmt->bindParam(":group_id", $_GET['group_id']);
                    $stmt->execute();
                    echo '<script>window.alert("Added event");</script>'; //debugging
                    //header("Location: index.php?group_id=".$_GET['group_id']);
                    exit();
                } catch (PDOException $e){
                  $errormsg = $e->getMessage();
                  //header("Location: redirect.php");
                }
            } else if($_GET['request'] == 3){ //add auth
                try{
                    $result_id = getUserId($_POST['authuser']);
                    if($result_id == 0){
                        echo 'No such user. Try again.';
                    } else {
                        //check if user follows the group
                        if(isUserFollowing($result_id, $_GET['group_id']) == 1){
                            //check if user is already authorized
                            if(isUserAuthorized($result_id, $_GET['group_id']) > 0){
                                echo 'User is already authorized. Try again.';
                            } else {
                                $stmt = $db->prepare("INSERT INTO group_auth
                                  (authuser_id, group_id) VALUES (:authuser_id, :group_id)");
                                $stmt->bindParam(":authuser_id", $result_id);
                                $stmt->bindParam(":group_id", $_GET['group_id']);
                                $stmt->execute();
                                echo '<script>window.alert("Added authorized user");</script>'; //debugging
                                header("Location: index.php?group_id=".$_GET['group_id']);
                                exit();
                            }
                        } else {
                            echo 'User is not following the group. Try again.';
                        }
                    }
                } catch (PDOException $e){
                  $errormsg = $e->getMessage();
                  header("Location: redirect.php");
                }
            } else if($_GET['request'] == 4){ //del auth
                try{
                    $result_id = getUserId($_POST['authuser']);
                    if($result_id == 0){
                        echo 'No such user. Try again.';
                    } else {
                        //check if user follows the group
                        if(isUserFollowing($result_id, $_GET['group_id']) == 1){
                            //check if creator is the one to be deleted
                            $result_auth = isUserAuthorized($result_id, $_GET['group_id']);
                            if($result_auth >= 3){
                                echo 'The group creator cannot be removed from authority. Try again.';
                            } else if($result_auth <= 0){
                                echo 'User isn\'t authorized. Try again.';
                            } else {
                                $stmt = $db->prepare("DELETE FROM group_auth
                                    WHERE authuser_id = :authuser_id AND group_id = :group_id");
                                $stmt->bindParam(":authuser_id", $result_id);
                                $stmt->bindParam(":group_id", $_GET['group_id']);
                                $stmt->execute();
                                echo '<script>window.alert("Deleted authorized user");</script>'; //debugging
                                header("Location: index.php?group_id=".$_GET['group_id']);
                                exit();
                            }
                        } else {
                            echo 'User is not following the group. Try again.';
                        }
                    }
                } catch (PDOException $e){
                  $errormsg = $e->getMessage();
                  header("Location: redirect.php");
                }
            } else if($_GET['request'] == 2){ //del event
                try{
                    foreach($_POST as $event_id){
                        $stmt = $db->prepare("DELETE FROM group_events
                            WHERE event_id = :event_id");
                        $stmt->bindParam(":event_id", $event_id);
                        $stmt->execute();
                        $stmt = $db->prepare("DELETE FROM events
                            WHERE event_id = :event_id");
                        $stmt->bindParam(":event_id", $event_id);
                        $stmt->execute();
                    }
                    echo '<script>window.alert("Deleted events");</script>'; //debugging
                    header("Location: index.php?group_id=".$_GET['group_id']);
                    exit();
                } catch (PDOException $e){
                  $errormsg = $e->getMessage();
                  header("Location: redirect.php");
                }
            }
        } else if(isset($_POST['group_name'])){ //adding a group
            if($_POST['group_desc']){
                //check if group is already made
                $group_id = getGroupId($_POST['group_name']);
                if ($group_id){
                    echo 'Group already exists. Try again.';
                } else {
                    $stmt = $db->prepare("INSERT INTO groups
                      (group_name, group_desc, group_creator)
                      VALUES (:group_name, :group_desc, :group_creator)");
                    $stmt->bindParam(":group_name", $_POST['group_name']);
                    $stmt->bindParam(":group_desc", $_POST['group_desc']);
                    $stmt->bindParam(":group_creator", $_SESSION['user_id']);
                    $stmt->execute();
                    $group_id = getGroupId($_POST['group_name']);

                    $stmt = $db->prepare("INSERT INTO group_users
                      (group_id, user_id)
                      VALUES (:group_id, :user_id)");
                    $stmt->bindParam(":group_id", $group_id);
                    $stmt->bindParam(":user_id", $_SESSION['user_id']);
                    $stmt->execute();
                    echo '<script>window.alert("Added group");</script>'; //debugging
                    header("Location: index.php?group_id=".$group_id);
                    exit();
                }
            } else {
                echo 'Please fill up the description.';
            }
        }
    }
?>
