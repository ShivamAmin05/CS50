-- Keep a log of any SQL queries you execute as you solve the mystery.
--list of all possible suspects
SELECT *
FROM people;
-- find the crime report for the CS50 duck robbery
SELECT *
FROM crime_scene_reports
WHERE street = "Humphrey Street"
    AND month = 7
    AND day = 28
    AND year = 2021;
--obtain the three interview accounts of the bakery robbery
SELECT *
FROM interviews
WHERE year = 2021
    AND month = 7
    AND day = 28;
-- obtain the license_plates of all the cars that left the bakery within ten minutes of the crime
SELECT *
FROM bakery_security_logs
WHERE year = 2021
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute > 15
    AND minute <= 25;

--obtain names of people who made a transaction on Leggett Street before the robbery
SELECT name
from people
WHERE id IN(
        SELECT person_id
        FROM bank_accounts
        WHERE account_number IN(
                SELECT account_number
                FROM atm_transactions
                WHERE year = 2021
                    AND month = 7
                    AND day = 28
                    AND atm_location = "Leggett Street"
            )
    );
--obtain the names of the people who exited the bakery within ten minutes of the robbery
SELECT name
FROM people
WHERE license_plate IN(
        SELECT license_plate
        FROM bakery_security_logs
        WHERE year = 2021
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute > 15
            AND minute <= 25
    );

--obatain name of the passengers on the earliest flight leaving fiftyville on the 29th
SELECT name
FROM people
WHERE passport_number IN(
        SELECT passport_number
        FROM passengers
        WHERE flight_id = (
                SELECT id
                FROM flights
                WHERE year = 2021
                    AND month = 7
                    AND day = 29
                    AND hour = (
                        SELECT MIN(hour)
                        FROM flights
                        WHERE year = 2021
                            AND month = 7
                            AND day = 29
                    )
            )
    );
--obtain names of people who made a phone call for the same duration as the robber
SELECT name
FROM people
WHERE phone_number IN(
        SELECT caller
        FROM phone_calls
        WHERE year = 2021
            AND month = 7
            AND day = 28
            AND duration < 60
    );
--obtain names of people who were on the flight, made a transaction, and were on the flight, and made a phone call
SELECT name
FROM people
WHERE name IN(
        SELECT name
        from people
        WHERE id IN(
                SELECT person_id
                FROM bank_accounts
                WHERE account_number IN(
                        SELECT account_number
                        FROM atm_transactions
                        WHERE year = 2021
                            AND month = 7
                            AND day = 28
                            AND atm_location = "Leggett Street"
                    )
            )
    )
    AND name IN(
        SELECT name
        FROM people
        WHERE license_plate IN(
                SELECT license_plate
                FROM bakery_security_logs
                WHERE year = 2021
                    AND month = 7
                    AND day = 28
                    AND hour = 10
                    AND minute > 15
                    AND minute <= 25
            )
    )
    AND name IN(
        SELECT name
        FROM people
        WHERE passport_number IN(
                SELECT passport_number
                FROM passengers
                WHERE flight_id = (
                        SELECT id
                        FROM flights
                        WHERE year = 2021
                            AND month = 7
                            AND day = 29
                            AND hour = (
                                SELECT MIN(hour)
                                FROM flights
                                WHERE year = 2021
                                    AND month = 7
                                    AND day = 29
                            )
                    )
            )
    )
    AND name IN(
        SELECT name
        FROM people
        WHERE phone_number IN(
                SELECT caller
                FROM phone_calls
                WHERE year = 2021
                    AND month = 7
                    AND day = 28
                    AND duration < 60
            )
    );
--robber is Bruce

--obtain partner's name, Robin
SELECT name
FROM people
WHERE phone_number = (
        SELECT receiver
        FROM phone_calls
        WHERE year = 2021
            AND month = 7
            AND day = 28
            AND duration < 60
            AND caller = (
                SELECT phone_number
                from people
                WHERE name == "Bruce"
            )
    );

--finds the city the the Robber is escaping to
SELECT city
FROM airports
WHERE id = (
        SELECT destination_airport_id
        FROM flights
        WHERE year = 2021
            AND month = 7
            AND day = 29
            AND hour = (
                SELECT MIN(hour)
                FROM flights
                WHERE year = 2021
                    AND month = 7
                    AND day = 29
            )
    );