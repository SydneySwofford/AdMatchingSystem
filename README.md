# Ad Matching System

This project matches ad's from incoming user requests based off of query data to the most relevant ad at the highest price.

## Build Instructions

1. Clone the repository to your laptop.
2. The solution is packaged entirely in the `AdMatchingSystem.sln`. Simply open, build, and run.
3. The output file will be generated as `output.txt` in the directory.
4. Tests can be run using the built-in Test Runner in Visual Studio.

## Class Diagram

![image](https://github.com/user-attachments/assets/e58ff68e-8ca3-462c-be2f-f4d1bc96be92)

## System Specification

1. **Document Control**
   - **Version**: 1.0
   - **Authors**: [Sydney Swofford]
   - **Date**: [8/29/2024]

2. **Introduction**
   - **Purpose**: This document outlines the specifications for the Ad Matching System designed to efficiently match ads based on incoming bid requests given a database of ads.
   - **Scope**: The system will handle incoming HTTP requests as they are read line by line, parse query parameters, select appropriate ads based on keywords and dimensions, calculate bids, and return the best-matching ad.

3. **System Overview**
   - **High-Level Description**: The Ad Matching System ingests bid requests through a stream, which contains details such as keywords, ad size, and user information like IP address, agent, and even device type. The system uses size and keyword information to match requests with pre-stored ads in an ad database, calculating the optimal ad based on predefined criteria that promote the highest bid selection.
   - **Objectives**:
     - Provide timely and accurate ad matches for incoming bid requests.
     - Maintain flexibility and scalability in ad matching logic.
     - Ensure high system performance with minimal latency.

4. **System Architecture**
   - **Modules**:
     - **AdManager**: Handles and loads ad data.
     - **MatchingEngine**: Contains the components that perform ad matching.
     - **RequestParser**: Manages request handling and manipulation.
     - **Utilities**: Contains utility components for output handling.

   - **Components**:
     - **RequestParser**: Parses incoming bid requests to extract relevant parameters.
     - **Request**: Stores data for individual requests.
     - **QueryStringGenerator**: Parses URL strings into query string elements of importance.
     - **AdLoader**: Loads ads from a database file into memory to reduce IO operations.
     - **AdStorer**: Stores ads loaded from memory into a vector and provides access for retrieval.
     - **AdSelector**: Selects potential ads based on request parameters and stores them in a vector.
     - **Ad**: Stores data for individual ads.
     - **BidCalculator**: Calculates the bid value for each selected ad.
     - **Matcher**: Orchestrates ad selection by matching the request with the best ad.
     - **OutputGenerator**: Handles outputting the result to a file.

   - **Interfaces**:
     - **IAd**: Passes `Ad` objects to other classes.
     - **IAdLoader**: Creates a concrete agreement of `AdLoader` operations for future extension.
     - **IAdStorer**: Passes the `AdStorer` to other classes.
     - **IAdSelector**: Passes the `AdSelector` to other classes.
     - **IBidCalculator**: Passes the `BidCalculator` to other classes.
     - **IMatcher**: Creates a concrete agreement of `Matcher` operations for future extension.
     - **IQueryStringParser**: Passes the `QueryStringParser` to other classes.
     - **IRequest**: Passes `Request` objects to other classes.
     - **IRequestParser**: Passes the `RequestParser` to other classes.

5. **Functional Requirements**
   - **Parsing Requests**:
     - Support multiple query formats.
     - Accurately extract all necessary fields.
   - **Matching Ads**:
     - Match based on exact size and at least one matching keyword.
     - Return the ad with the highest bid value where applicable.
   - **Error Handling**:
     - Handle bad requests and system errors.

6. **Non-Functional Requirements**
   - **Performance**:
     - Handle 10,000 requests.
   - **Scalability**:
     - The system is scalable to handle more request input types.
     - The system is scalable to store more request information.
   - **Maintainability**:
     - The code is extremely modular and easily testable.

## Sequence Diagram

The flow of a request as it comes from the "client" (being read line by line).

![image](https://github.com/user-attachments/assets/bfaba9d6-b972-4c46-8a51-468ada2c83a9)

## Testing

Testing is accomplished through Microsoft's native unit testing environment, and tests are accessible through the Test Explorer once the project is built. Tests are written in the `TC_TN` format to denote like tests as `TC` and test number as `TN`, along with a short comment to describe the general test. An image of the testing environment and common labeling can be seen below:

![Testing Environment](https://github.com/user-attachments/assets/97f5a068-4acc-4282-aa5f-e7272e3b153f)

### Test Plan

1. **Introduction**
   - The purpose of this test plan is to outline the testing efforts for the Ad Matching system, with the goal of achieving 90% code coverage.

2. **Test Items**
   - RequestParser
   - Request
   - QueryStringGenerator
   - AdLoader
   - AdStorer
   - AdSelector
   - Ad
   - BidCalculator
   - Matcher
   - OutputGenerator

3. **Features to be Tested**
   - All concrete functions of test items to ensure each function executes as expected.

4. **Approach**
   - Unit testing is the main approach for this test plan. However, component testing should be added in the future to cover component-to-component relationships.

5. **Pass/Fail Criteria**
   - Pass/fail criteria are based on the ASSERT statements in each test. Tests will either pass or fail based on asserting the expected result.

6. **Testing Environment**
   - Microsoft Native Unit Testing for C++, Visual Studio.

7. **Test Deliverables**
   - Upon successful test run, visual checks from Native Unit Testing will show if any tests have failed. Failure of tests indicates that the system is not working as intended and must be debugged.

## Part III: iPad-Specific Ad Serving

If a client only wants to serve specific ads to strictly iPad users, more data would need to be introduced to the system to store and handle device-specific information. This would involve introducing new data members for the `Request` object to additionally parse user device data, which could also be obtained through the HTTP request.

### Assumptions That Would Need to Change

- **Ad Selection**:
  - Ad selection has been based on uniform criteria, primarily size matching and keyword matching. However, it would now need to be expanded to handle device type filtering.
  - Each `Ad` class could be extended to include a `targetDevice(string& deviceType)` method, which would check if a given ad targets a particular device. Ads not targeting the correct device could then be excluded from the `AdSelector` vector of valid ads.

- **Request Parsing**:
  - The availability of information about whether or not a user is on an iPad would need to be determined through the request and added to the request parsing logic.
  - A function `getDeviceType()` could be implemented to grab the device type from the HTTP request and store it in a Boolean `isIpad`.

### Performance Considerations

- **Complexity**:
  - The complexity of the system will increase due to additional checks, which will increase the time it takes to select ads.

- **Storage**:
  - More information from requests and additional criteria in ad selection impose larger storage requirements on the system, which could create runtime slowdowns.

## Future Work

There are always room for improvement.

- **Security Considerations**  
  The application handles potentially sensitive user data as requests are consumed. Considerations to protect this user data from malicious actors could enhance the security of the application.

- **Extend Current Objects**  
  Current objects can be extended for additional functionality to create a more robust system. This includes parsing device data into request objects and storing device preference data in ad objects. Due to the extensible nature of the code, more features could be added as they are conceived.

- **User Interface for Logging/Monitoring**  
  A user interface could be added to monitor or log the system’s operations. Additionally, a GUI could be created to run the system, bypassing the need for access to the source code for system testers.

- **Expand Unit Test Coverage & Ad Coverage Monitor**  
  Further thought could be put into improving tests for more complex areas of the code. Adding a unit test monitor could help in effectively tracking code coverage. This would ensure that the product code is thoroughly tested.

- **Implement Component Tests**  
  Component tests were not implemented to test the interaction between classes/modules due to time constraints. However, they are crucial for good code coverage and allow for confident refactoring. These tests ensure that any changes in desired implementation or outcome will be apparent in the test results.

