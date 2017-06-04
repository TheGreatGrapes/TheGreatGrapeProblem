/*
 * ///////////////// Multi-Agent Traffic simulation ////////////////
 * 
 * Version 2.0
 * 
 * Agent number:
 * Single agent
 * 
 * Functionalities: 
 * Report position / Move with **ACCELERATION** / Make decision at crossroad
 * 
 * Explanation:
 *      An agent (Car) is initialized at (0,0) in the beginning. 
 *      It can choose from different path (equations) to go, if (0,0), then up or right,
 *      Our map provides at least two options at the corner, at most four options at the crossroad.
 *      The car is allowed to turn back, it moves and stops at every node, and decides randomly 
 *      to connet to different pathes. 
 *      Simulation time is set, yet according to the postion of object, it might jump to the next 
 *      if-statement, which would not counted by the counter.
 * 
 * This is how the map looks like (but no 2D array needed) :
 * 
 *                        (120,240)
 *       (0,240) *  *  *  *  *  *  *  *  * (240,240)
 *               *           *           *
 *               *           *           *
 *               *           *           *
 *               *           * (120,120) *
 *       (0,120) *  *  *  *  *  *  *  *  * (240,120)
 *               *           *           *
 *               *           *           *
 *               *           *           *
 *               *           *           *
 *         (0,0) *  *  *  *  *  *  *  *  * (240,0)
 *                        (120,0)          
 * 
 *      
 *  There're two classes: Car & Map
 *  Car class 
 *      1. can report position (or directly access since the variable is public)
 *      2. is used as an argument a function in Map class
 *      3. has indexX & indexY as the coordinates of Car object (x,y)
 *      4. has function called check() to check current position of object 
 *      5. 's object is initilized at (0,0)
 * 
 *  Map class
 *      1. has 6 functions, each of them represents one street. 
 *      2. is essentially an update center, updating the position of the imported object.
 *      3. E.g. 
 * 
 *         yEquals_0(Car* obj,  bool dir)
 *          ＾             ＾          ＾       
 *     Name of street    Object   Forward/Backward
 
        double velo = 0.0;                            // Initialze a temperary variable 
        double tempX = obj->indexX;                   // Remember the initial position
        
        do{                                           // Accelerating //
            velo += obj->Acc;                         // Velocity is updated by acceleration
            checkDirX(obj, velo, dir);                // Check whether X should be increasing or decreasing
            obj->indexY = obj->indexX * 0 + 0;        // Updateing Y coordinate according to X 
            printPos(obj, velo);                      // Outputing position
        }while(fabs(obj->indexX - tempX) < dist/3);   // Accelerating till 1/3 of the dist is covered
        
        do{                                           // Cruising //
            checkDirX(obj, velo, dir);                // Check whether X should be increasing or decreasing
            obj->indexY = obj->indexX * 0 + 0;        // Updateing Y coordinate according to X
            printPos(obj, velo);                      // Outputing position
        }while(fabs(obj->indexX - tempX) <= dist*2/3);// Remain constant speed for another 1/3 of distance
        
        do{                                           // Breaking //
            velo -= obj->Acc;                         // Velocity is updated by acceleration
            checkDirX(obj, velo, dir);                // Check whether X should be increasing or decreasing
            obj->indexY = obj->indexX * 0 + 0;        // Updateing Y coordinate according to X
            printPos(obj, velo);                      // Outputing position
        }while( dist - fabs(obj->indexX - tempX) > 1);// Deaccelerating till 1 unit away from junction.
    
        if (dir == 1) obj->indexX = tempX + dist;     // Hit the break right at junction, making sure it does not go over 
        else          obj->indexX = tempX - dist;     // 
        velo = 0;                                     // Same here
        printPos(obj, velo);                          // Outputing position
 *      
 *  Possible tasks to further work on:
 *      1. Initialize a random position for the object, not only on crossroads.
 *      2. Pack the if-statement and switches into individual functions, make the main() cleaner.
 *      3. How to add another object to simulation? Array?
 *      4. Collision avoidance / Car follow
 *      5. Better way of implementing map?
 * 
 *   First written  06.05.2017 01:42 TIMPERATOR
 *   Last updated   08.05.2017 12:35 TIMPERATOR & ARINDAM (Acceleration module added)
*/