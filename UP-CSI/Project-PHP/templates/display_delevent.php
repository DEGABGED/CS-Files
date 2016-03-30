<div class="form" id="addauth_form">
    <h3><?php echo getGroupName($_GET['group_id']) ?></h3>
    <h4>Remove Events</h4>
    <form action="<?php $_SERVER['PHP_SELF'].'?request='.$_GET['request'].'&group_id='.$_GET['group_id'] ?>" method="post">
        <?php
            try{
                $stmt = $db->prepare("SELECT event_id FROM group_events WHERE group_id = :group_id");
                $stmt->bindParam(":group_id", $_GET['group_id']);
                $stmt->execute();
                $result = $stmt->fetch();
                $stmt2 = $db->prepare("SELECT event_name, event_desc, event_creator FROM events WHERE event_id = :event_id");
                $isDeletable = 0;
                while($result['event_id']){
                    //echo 'event_id: '.$result['event_id'].'<br/>';
                    $stmt2->bindParam(":event_id", $result['event_id']);
                    $stmt2->execute();
                    $result2 = $stmt2->fetch();
                    if(isset($result2['event_creator']) && $result2['event_creator'] == $_SESSION['user_id']){
                        echo '<input type="checkbox" name="event_id'.$result['event_id']
                        .'" value="'.$result['event_id'].'">'.$result2['event_name'].': '
                        .$result2['event_desc'].'<br />';
                        $isDeletable = 1;
                    }
                    $result = $stmt->fetch();
                }

                if($isDeletable){
                  echo '<br /><input type="submit">';
                } else {
                  echo '<br /><p>&nbsp;No deletable events.</p>';
                }
            } catch (PDOException $e){
                $errormsg = $e->getMessage();
                echo '<script>window.alert("'.$errormsg.'");</script>';
            }
        ?>
    </form>
</div>
