SELECT * FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = 'Humphrey Street';
SELECT * FROM interviews WHERE month = 7 AND day = 28;
SELECT * FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND (minute >= 25 AND minute <= 35);
SELECT * FROM people WHERE license_plate = '1106N58';
SELECT * FROM phone_calls WHERE caller = '(286) 555-6063' AND day = 28 AND month = 7 AND duration < 60;
SELECT * FROM people WHERE phone_number = '(676) 555-6554';
SELECT * FROM airports WHERE city = 'Fiftyville';
SELECT * FROM flights WHERE origin_airport_id = 8 AND month = 7 AND day = 29 ORDER BY hour LIMIT 1;
SELECT * FROM airports WHERE id = 4;