-- Keep a log of any SQL queries you execute as you solve the mystery.

-- All you know is that the theft took place on *July 28, 2020* and that it took place on *Chamberlin Street*.
-- 取得犯人目擊報告
SELECT description
FROM crime_scene_reports
WHERE year = 2020 AND month = 7 AND day = 28 AND street = 'Chamberlin Street';

-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
-- Interviews were conducted *today* with three witnesses who were present at the time — each of their interview transcripts mentions the *courthouse*.

SELECT name, transcript
FROM interviews
WHERE year = 2020 AND month = 7 AND day = 28 AND transcript LIKE '%courthouse%';
-- 取得證詞
-- Ruth : Sometime *within ten minutes* of the theft, I saw the thief get into a car in the courthouse parking lot and *drive away*.
--        If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.

    SELECT *
    FROM courthouse_security_logs
    WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25 AND activity = 'exit';
    -- 取得車牌號碼
    -- id | year | month | day | hour | minute | activity | license_plate
    -- 260 | 2020 | 7 | 28 | 10 | 16 | exit | 5P2BI95
    -- 261 | 2020 | 7 | 28 | 10 | 18 | exit | 94KL13X
    -- 262 | 2020 | 7 | 28 | 10 | 18 | exit | 6P58WS2
    -- 263 | 2020 | 7 | 28 | 10 | 19 | exit | 4328GD8
    -- 264 | 2020 | 7 | 28 | 10 | 20 | exit | G412CB7
    -- 265 | 2020 | 7 | 28 | 10 | 21 | exit | L93JTIZ
    -- 266 | 2020 | 7 | 28 | 10 | 23 | exit | 322W7JE
    -- 267 | 2020 | 7 | 28 | 10 | 23 | exit | 0NTHK55

-- Eugene : I don't know the thief's name, but it was someone I recognized.
--          Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on *Fifer Street* and saw the thief there *withdrawing* some money.

    SELECT atm_transactions.*, people.name AS account_name
    FROM atm_transactions
    JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
    JOIN people ON people.id = bank_accounts.person_id
    WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = 'withdraw' AND atm_location = 'Fifer Street'
    AND people.license_plate in (
        SELECT license_plate
        FROM courthouse_security_logs
        WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25 AND activity = 'exit'
    );
    -- 取得atm帳號,帳戶名
    -- id | account_number | year | month | day | atm_location | transaction_type | amount | account_name
    -- 267 | 49610011 | 2020 | 7 | 28 | Fifer Street | withdraw | 50 | Ernest
    -- 336 | 26013199 | 2020 | 7 | 28 | Fifer Street | withdraw | 35 | Russell
    -- 288 | 25506511 | 2020 | 7 | 28 | Fifer Street | withdraw | 20 | Elizabeth
    -- 246 | 28500762 | 2020 | 7 | 28 | Fifer Street | withdraw | 48 | Danielle

-- Raymond : As the thief was leaving the courthouse, they called someone who talked to them for *less than a minute*.
--           In the call, I heard the thief say that they were planning to *take the earliest flight out of Fiftyville tomorrow*.
--           The thief then asked the person on the other end of the phone to purchase the flight ticket.

    SELECT phone_calls.*, C.name AS callerName, R.name AS receiverName, C.passport_number AS callerPassport
    FROM phone_calls
    JOIN people AS C ON C.phone_number = phone_calls.caller
    JOIN people AS R ON R.phone_number = phone_calls.receiver
    WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60
    AND C.name in (
        SELECT people.name
        FROM atm_transactions
        JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
        JOIN people ON people.id = bank_accounts.person_id
        WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = 'withdraw' AND atm_location = 'Fifer Street'
        AND people.license_plate in (
            SELECT license_plate
            FROM courthouse_security_logs
            WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25 AND activity = 'exit'
        )
    );

    -- 取得通聯記錄 , thief => caller, receiver => ACCOMPLICE
    -- id | caller | receiver | year | month | day | duration | callerName | receiverName | callerPassport
    -- 233 | (367) 555-5533 | (375) 555-8161 | 2020 | 7 | 28 | 45 | Ernest | Berthold | 5773159633
    -- 255 | (770) 555-1861 | (725) 555-3243 | 2020 | 7 | 28 | 49 | Russell | Philip | 3592750733

    SELECT flights.*, O.city, D.city FROM flights
    JOIN airports AS O ON O.id = flights.origin_airport_id
    JOIN airports AS D ON D.id = flights.destination_airport_id
    WHERE year = 2020 AND month = 7 AND day = 29 AND O.city = 'Fiftyville'
    ORDER BY hour, minute
    LIMIT 1;
    -- 取得航班資訊
    -- id | origin_airport_id | destination_airport_id | year | month | day | hour | minute | city | city
    -- 36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20 | Fiftyville | London

    SELECT passengers.*, people.name AS passengersName
    FROM passengers
    JOIN people ON people.passport_number = passengers.passport_number
    WHERE flight_id = 36 AND passengers.passport_number in (
        SELECT C.passport_number
            FROM phone_calls
            JOIN people AS C ON C.phone_number = phone_calls.caller
            JOIN people AS R ON R.phone_number = phone_calls.receiver
            WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60
            AND C.name in (
                SELECT people.name
                FROM atm_transactions
                JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
                JOIN people ON people.id = bank_accounts.person_id
                WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = 'withdraw' AND atm_location = 'Fifer Street'
                AND people.license_plate in (
                    SELECT license_plate
                    FROM courthouse_security_logs
                    WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25 AND activity = 'exit'
                )
            )
    );

    -- 取得乘客資訊(犯人)
    -- flight_id | passport_number | seat | passengersName
    -- 36 | 5773159633 | 4A | Ernest
