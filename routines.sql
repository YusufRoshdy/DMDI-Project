DELIMITER $$
CREATE PROCEDURE q1(v_pid INT)
BEGIN
	-- Q1
	SELECT doctors.* 
	FROM appointments, doctors,
		 (SELECT * FROM appointments WHERE p_id = v_pid ORDER BY time_slot DESC limit 1) as date1 -- p_id need to be sent
	where date(date1.time_slot) = date(appointments.time_slot) and date1.p_id = appointments.p_id
		  and doctors.d_id = appointments.d_id
		  and (doctors.first_name like 'M%' OR doctors.first_name like 'L%') != (doctors.last_name like 'M%' OR doctors.last_name like 'L%');
END $$
DELIMITER ;

DELIMITER $$
CREATE PROCEDURE q2()
BEGIN
	DECLARE v_did INT;
    DECLARE v_slot INT;
    DECLARE v_total INT;
    DECLARE v_average INT;
    DECLARE v_s INT;
    DECLARE v_d INT;
    
	DECLARE done INT DEFAULT FALSE;
    
	DECLARE cur CURSOR
	FOR SELECT 
			d_id
		FROM 
			doctors;
	DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
	OPEN cur;
    
    DROP TEMPORARY TABLE IF EXISTS statistics;
	CREATE TEMPORARY TABLE statistics 
	(d_id INT, slot INT, week_day INT, total INT, average INT);
	 
	myloop: LOOP
		FETCH NEXT FROM cur INTO 
			  v_did;
    
		IF done THEN
			LEAVE myloop;
		END IF;
        
        -- loop for day
        set v_d = 1;
		WHILE v_d <= 7
		DO
        
			-- loop for slots
			set v_s = 10;
			WHILE v_s <= 12
			DO
				SELECT COUNT(*) INTO v_total 
				FROM appointments 
				WHERE Time(time_slot) = concat(v_s, ':00:00')
					AND weekday(time_slot) = v_d
					AND d_id = v_did;
				INSERT INTO statistics VALUES(v_did, v_s, v_d, v_total, v_total/52.0);
				SET v_s = v_s + 1;
			END WHILE;
            SET v_d = v_d + 1;
		END WHILE;
			
	  END LOOP;
	 
	CLOSE cur;

	SELECT * FROM statistics;
END $$
DELIMITER ;

DELIMITER $$
CREATE PROCEDURE q3()
BEGIN
	-- statements
	DECLARE v_pid INT;
    
    DECLARE sz INT;
    DECLARE sz1 INT;
    DECLARE sz2 INT;
    DECLARE sz3 INT;
    
    DECLARE done INT DEFAULT FALSE;
	DECLARE cur CURSOR
	FOR SELECT 
		p_id
	FROM 
		appointments;
	DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
	OPEN cur;
	
    DROP TEMPORARY TABLE IF EXISTS v_patients;
	CREATE TEMPORARY TABLE v_patients 
	(pid INT);
    
	myloop: LOOP
		FETCH NEXT FROM cur INTO 
            v_pid;
		IF done THEN
			LEAVE myloop;
		END IF;
    
		SELECT COUNT(*) INTO sz  FROM appointments 
                WHERE time_slot > TIMESTAMPADD(DAY, -7, NOW())
                      and time_slot <= NOW() and p_id = v_pid;
		
		SELECT COUNT(*) INTO sz1  FROM appointments 
                WHERE time_slot > TIMESTAMPADD(DAY, -14, NOW())
                      and time_slot <= TIMESTAMPADD(DAY, -7, NOW()) and p_id = v_pid;
		
		SELECT COUNT(*) INTO sz2  FROM appointments  
                WHERE time_slot > TIMESTAMPADD(DAY, -21, NOW())
                      and time_slot <= TIMESTAMPADD(DAY, -14, NOW()) and p_id = v_pid;
                    
		
		SELECT COUNT(*) INTO sz3  FROM appointments 
                 WHERE time_slot > TIMESTAMPADD(DAY, -28, NOW())
                      and time_slot <= TIMESTAMPADD(DAY, -21, NOW()) and p_id = v_pid;
                    
		IF(sz > 1 AND sz1 > 1 AND sz2 > 1 AND sz3 > 1) THEN
            insert into v_patients values(v_pid);
		END IF;
    END LOOP;
	select distinct patients.* from v_patients, patients where patients.p_id = v_patients.pid;
	CLOSE cur;
END $$
DELIMITER ;

DELIMITER $$
CREATE PROCEDURE q4()
BEGIN
	DECLARE v_pid INT;
	DECLARE v_sum INT DEFAULT 0;
    DECLARE v_age INT;
	DECLARE v_dob DATE;
	DECLARE v_cnt INT;
    
    DECLARE done INT DEFAULT FALSE;

	DECLARE cur CURSOR
	FOR SELECT 
			p_id
		FROM 
			patients;
	DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
	OPEN cur;
	 
	FETCH NEXT FROM cur INTO 
		v_pid;
	 
	myloop: LOOP
		FETCH NEXT FROM cur INTO 
			v_pid;
        
        IF done THEN
			LEAVE myloop;
		END IF;
		
		SELECT date_of_birth INTO v_dob 
		FROM patients 
		WHERE p_id = v_pid;

		SET v_age = TIMESTAMPDIFF(YEAR, v_dob, NOW());
		SELECT COUNT(*) INTO v_cnt FROM appointments WHERE time_slot >= TIMESTAMPADD(DAY, -30, NOW()) and p_id = v_pid;

		IF(v_age < 50) THEN
			IF(v_cnt < 3) THEN 
				SET v_sum = v_sum + v_cnt * 200;
			ELSE SET v_sum = v_sum + v_cnt * 250;
            END IF;
		ELSE
		  BEGIN
			IF(v_cnt < 3) THEN 
				SET v_sum = v_sum + v_cnt * 400;
			ELSE SET v_sum = v_sum + v_cnt * 500;
            END IF;
		  END;
		END IF;
	END loop;
	CLOSE cur;
	SELECT v_sum;
END $$
DELIMITER ;

DELIMITER $$
CREATE PROCEDURE q5()
BEGIN
	DECLARE v_did INT;
    
    DECLARE v_cnt INT DEFAULT 0;
	DECLARE v_cnt2 INT DEFAULT 0;
	DECLARE v_i INT;
    
	DECLARE done INT DEFAULT FALSE;
    
	DECLARE cur CURSOR
	FOR SELECT 
			d_id
		FROM 
			doctors;
	DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
	OPEN cur;
    
    DROP TEMPORARY TABLE IF EXISTS v_doctors;
	CREATE TEMPORARY TABLE v_doctors 
	 (did INT);
	 
	myloop: LOOP
		FETCH NEXT FROM cur INTO 
			  v_did;
    
		IF done THEN
			LEAVE myloop;
		END IF;
        
        SET v_cnt = 0;
        SET v_cnt2 = 0;
		SET v_i = 1;
		WHILE v_i <= 10
		DO
		  SELECT COUNT(*) INTO v_cnt FROM appointments WHERE time_slot >= TIMESTAMPADD(YEAR, -v_i, NOW()) and d_id = v_did;

		  IF(v_cnt >= 100) THEN 
			SET v_cnt2 = v_cnt2 + 1;
		  END IF; 

		  SET v_i = v_i + 1;
		END WHILE;
		

		IF(v_cnt2 >= 10)
		THEN
		   IF NOT EXISTS(SELECT * FROM v_doctors where did = v_did) THEN
			INSERT INTO v_doctors VALUES(v_did);
		   END IF;
		END IF;

			
	  END LOOP;
	 
	CLOSE cur;

	SELECT P.* FROM doctors P
	JOIN v_doctors T
	ON P.d_id = T.did;
END $$
DELIMITER ;