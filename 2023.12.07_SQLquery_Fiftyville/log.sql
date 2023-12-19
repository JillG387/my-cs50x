-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Above each query, label each with a comment describing why you’re running the query
-- and/or what information you’re hoping to get out of that particular query.

-- Known: Mystery of the stolen duck. The theft took place on July 28, 2021 on Humphrey Street
--        Thief stole the duck & then took a flight out of town with the help of an accomplice


-- Obtain the crime scene report information
SELECT description FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND street = 'Humphrey Street';

-- Theft took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time
-- each of their interview transcripts mentions the bakery.
-- Littering took place at 16:36. No witnesses


-- Obtain interview information
SELECT name, transcript FROM interviews
WHERE month = 7 AND day = 28 AND year = 2021;

-- Ruth mentioned sometime within ten minutes of the theft (theft took place at 10:15am) she saw the thief get into a car in the bakery parking lot and drive away.
--      She suggested looking at the security footage from the bakery parking lot and look for cars that left the lot in that time frame.
-- Eugene doesn't know the thief's name but it was someone he recognized. Earlier this morning, before arriving to Emma's bakery, he was walking by the
--        ATM on Leggett street and saw the thief there withdrawing money.
-- Raymond saw the thief call someone who talked to them for less than a minute as he was leaving the bakery. He herd the theif say they were planning to take
--         the earliest flight out of Fiftyville tomorrow. He then asked the person on the other end of the phone to purchase the flight.


-- Looking at security footage from the bakery parking lot
SELECT bakery_security_logs.activity, bakery_security_logs.license_plate, people.name FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE bakery_security_logs.year = 2021
AND bakery_security_logs.month = 7
AND bakery_security_logs.day = 28
AND bakery_security_logs.hour = 10
AND bakery_security_logs.minute >= 15
AND bakery_security_logs.minute <=25;

-- This query 8 results: Vanessa, Bruce, Barry, Luca, Sofia, Iman, Diana, Kelsey


-- Looking at the money withdraw activity for the ATM on Leggett street by comparing people, bank accounts, and atm transactions
SELECT people.name, atm_transactions.transaction_type FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE atm_transactions.year = 2021
AND atm_transactions.month = 7
AND atm_transactions.day = 28
AND atm_location = 'Leggett Street'
AND atm_transactions.transaction_type = 'withdraw';

-- Resulted in 8 names: Bruce, Diana, Brooke, Kenny, Iman, Luca, Taylor, Benista
-- What I know now - Bruce, Diana, Iman, Luca are in both lists.


-- Looking at the phone calls, flights, passengers, airports to obtain flight plans, city traveled to, and the accomplice.
-- Thief called someone when he left the bakery and talked for less then a minute mentioned wanting to leave Fiftyville on the earliest flight tomorrow (location)
-- and asked the person to buy the flight (the accomplice)

-- Examine the phone call and names
SELECT * FROM phone_calls
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60;

SELECT people.name, phone_calls.caller, phone_calls.year, phone_calls.month, phone_calls.day, phone_calls.duration
FROM phone_calls
JOIN people ON phone_calls.caller = people.phone_number
WHERE phone_calls.year = 2021
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration < 60;

-- Names of the callers are Sofia, Kelsey, Bruce, Kelsey, Taylor, Diana, Carina, Kenny, Benista
-- Common names consistantly appearing each time to this point - Bruce and Diana

-- Examine airports to look for Fiftyville
SELECT * FROM airports;
-- Fiftyville's 3-letter airport identifier is CSF, id = 8

-- Look for flights out of Fiftyville
SELECT flights.*, origin.full_name AS origin_airport, destination.full_name AS destination_airport
FROM flights
JOIN airports origin ON flights.origin_airport_id = origin.id
JOIN airports destination ON flights.destination_airport_id = destination.id
WHERE origin.id = 8 AND flights.year = 2021 AND flights.month = 7 AND flights.day = 29
ORDER BY flights.hour, flights.minute;

-- The first flight out of Fiftyville is to LaGuardia Airport in New York, flight id 36


-- Look at the passenger list to see which one is on the flight (Bruce or Diana). Given the third witness interview saying "he", I fully expect to see Bruce's name.
SELECT people.name FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
WHERE passengers.flight_id = 36
AND people.name IN ('Bruce', 'Diana');
-- Result, Bruce is on the flight

-- Looking for the accomplice. Who did Bruce call to purchase the airline ticket?
SELECT caller2.name AS receiver
FROM phone_calls
JOIN people caller1 ON phone_calls.caller = caller1.phone_number
JOIN people caller2 ON phone_calls.receiver = caller2.phone_number
WHERE caller1.name = 'Bruce'
AND phone_calls.year = 2021 AND phone_calls.month = 7 AND phone_calls.day = 28
AND phone_calls.duration < 60;
-- Receiver is Robin

-- So it turns out Batman, Bruce, is our thief who escaped to New York LaGuardia Airport. He called Robin who is the accomplice.
