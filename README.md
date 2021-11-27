# RelaxiTaxi
A C++ console application build to develop a backend clone quite similar to that of  Uber/OLA.

Technologies Used:
1. C++ console application.
2. MySql Database.

Features
1. Reusable functions that perform CRUD operations & can be reused depending upon queries.
2. After a driver registers, he first has to be verified by Employee before being able to start taking trips,which is also a part of software.
3. A trip linked with a particular driver depending upon the source of customer and the driver's current location.
4. After succcessful completion of trip the parameters of Driver like (Current Location,Number Of Trips,Reviews,Booking) gets updated.
5. Reviews taken from customer and updated in driver database.

ID Generation(Unique)
1. ID for new driver and customer generated by getting a mex value, so that ID lost by drivers removed can be reused.
2. ID for new trips generated in an increasing order since all trips till date are stored in database and we want no duplicacy.

Flow Diagram:
![Project_Diagram](https://user-images.githubusercontent.com/40807530/143618205-bca99e5d-414d-48fc-94f6-43ea10e9d773.jpeg)

Database
1. Driver Table
2. Customer/Passenger Table
3. New Trips Table(Contains records of New Trips By registered Customers)
4. Booked Trips Table(Contains records of trips accepted by drivers in nearby region)
5. Past Trips(Whole Collection of Trips Done Till Now that can be queried upon by Driver as well as Customer)

CRUD operations performed using MySQL syncronous queries.

ER Diagram
![ERDiagram](https://user-images.githubusercontent.com/40807530/143681851-40b7c72a-4393-4493-9d6f-090c96ea3bdf.jpeg)
