            /************************************************************************
            *************************************************************************
            *************************************************************************
            * --------------------------------------------------------------------- *
            *** -------------- C PROGRAMMING PX270 FINAL PROJECT ---------------- ***
            * --------------------------------------------------------------------- *
            *** ---------------- RESTRICTED THREE BODY PROBLEM ------------------ ***
            * --------------------------------------------------------------------- *
            *************************************************************************
            * --------------------------------------------------------------------- *
            *** ------------------------- edward-antram-------------------------- ***
            * --------------------------------------------------------------------- *
            *************************************************************************
            *************************************************************************
            *************************************************************************/



/**************************************************************************************************
 **************************************************************************************************
 * ---------------------------------------------------------------------------------------------- *
 *** -------------------------------------- three_body.c  ------------------------------------- ***
 * ---------------------------------------------------------------------------------------------- *
 **************************************************************************************************
 * ---------------------------------------------------------------------------------------------- *
 *** ----- Computes the trajectory of a free particle of mass unity for the 'Restricted Three - ***
 *** ----- Body Problem', with two fixed point-like variable masses at (-1,0) and (1,0) ------- ***
 * ---------------------------------------------------------------------------------------------- *
 *** ----- Project was extended to run simulations of a number n free particles, one after ---- ***
 *** ----- another. The particles do not interact with eachother. ----------------------------- ***
 * ---------------------------------------------------------------------------------------------- *
 **************************************************************************************************
 * ---------------------------------------------------------------------------------------------- *
 *** ----- User defines the number of free particles to simulate, the mass of the two fixed --- ***
 *** ----- bodies, the initial position and velocity of each free particle, and boundaries ---- ***
 *** ----- in which to run the simulation (when prompted). ------------------------------------ ***
 * ---------------------------------------------------------------------------------------------- *
 *** ----- When the particle collides with either one of the two fixed bodies or the ---------- ***
 *** ----- user-defined boundary, the program stops. If no collision occurs, the -------------- ***
 *** ----- program stops when after a number of steps chosen within the program (n) ----------- ***
 * ---------------------------------------------------------------------------------------------- *
 **************************************************************************************************
 * ---------------------------------------------------------------------------------------------- *
 *** ---------------- Data from trajectory is outputed to file: "three_body.txt" -------------- ***
 * ---------------------------------------------------------------------------------------------- *
 **************************************************************************************************
 **************************************************************************************************/



                        /**************************************************
                         **************************************************
                         ** -------------- PROBLEM DIAGRAM ------------- **
                         **************************************************
                         *                                                *
                         *                                                *
                         *                                                *
                         *                       ^                        *
                         *        ^              .                        *
                         *        |              .                        *
                         *        o-->           .                        *
                         * (x0,y0),(v0_x,v0_y)   .                        *
                         *                       .                        *
                         *                       .                        *
                         *                       .                        *
                         *       . . . . m_a . . . . . m_b . . . . . >    *
                         *                       .                        *
                         *              (-1,0)   .    (1,0)               *
                         *                       .                        *
                         *                       .                        *
                         *                       .                        *
                         *                       .                        *
                         *                       .                        *
                         *                                                *
                         **************************************************
                         * - Particle has initial position (x0,0y) and -- *
                         * ------- initial velocity (v0_x, v0_y) -------- *
                         **************************************************
                         **************************************************/





#include<stdlib.h>
#include<stdio.h>
#include <math.h>


int main (int argc, char* argv[])
{

    

    
                                /***********************************
                                ++ PART 1 - SIMULATION PARAMETERS ++
                                ************************************/
    
    
    
    double m_a=0,m_b=0,time[200000]; /* initialise mass A & mass B as well as time array */
    int x_boundary=0;
    int y_boundary=0;
    int w=0; /* used in PART 2 */
    double sen=0.05; /* used in PART 4 */
    
    /* The user must enter a number of particles (integer value). Whilst the simulation runs well
     with many particles, fewer 'intricacies' are encountered and I advise first testing the program 
     a few times with one particle before attempting to use many */
    
    int b=0;
    printf(" \n Please enter number of particles to simulate \n");
    scanf( "%d", &b);
    
    /* The user must enter boundaries in which to run the simulation (x and y). This is to contain 
     data, as a particle that has been released from orbit may be less interesting. This is also 
     useful for graphing as it means just the zone of interest vcan be studied */
    
    
    printf(" \n Please enter boundary for x values - set to large x (...>200) for no boundary \n");
    scanf( "%d", &x_boundary);
    
    printf(" \n Please enter boundary for y values - set to large y (...>200)hav for no boundary \n");
    scanf( "%d", &y_boundary);
    
    /* The user must enter the mass of each fixed body, this can be positive but also null or negative.
     I have allowed all values as it could lead to potentially interesting results */
    
    printf(" \n Please enter mass of body m_a situated at (-1,0) \n");
    scanf( "%lf", &m_a);
    printf(" \n Please enter mass of body m_b situated at (1,0) \n");
    scanf( "%lf", &m_b);
    
    printf(" *** You will be asked to enter a set of coordinates and velocities for each particle *** ");
    
    
    
    
    
    
    
    
                            /***********************************
                            +++ PART 2 - PARTICLE PARAMETERS +++
                            ************************************/
    

    
    /* initialising w which will be used as a counter for the "for" loop which runs the program once for
     each particle */
    
        for ( ; w<b ; w++) {
 
    /* initialising time stem, x and y arrays, x and y initial velocities and accelerations */
    
            double dt=0.005, x[200000],y[200000],x_v,y_v,a_x[200000],a_y[200000];
           
    int n;
    FILE* output=fopen("three_body.txt", "a");
    /* I've chosen to use the ('a') option for file creation because this allows the trajectory of each 
     particle to be added at the end of the previous particle's trajectory on the same file - however, 
     rather than going to the next line, this continues on the same line. This has not created any 
     problems for me because MATLAB is able to recognise and compute it. However, if this does not work */
    
            
        /***********************************************************************
        ************* IF THERE IS AN ISSUE COMPUTNIG THE FILE OUTPUT ***********
        ************* RUN SIMULATION WITH ONLY ONE PARTICLE ********************
        ***********************************************************************/
            
            
                printf(" *** Define next particle *** ");
    
    /* User must enter initial coordinates and velocities for each particle, this is done once for each
     particle - the particles do not interact with each other, however this could be likened to comets 
     passing near a binary star system - their mutual attraction is negligeable compared to that of the stars */
            
    printf(" \n Please enter initial x coordinate of particle \n");
    scanf( "%lf", &x[0]);
    printf(" \n Please enter initial y coordinate of particle \n");
    scanf( "%lf", &y[0]);
    printf(" \n Please enter initial x velocity of particle \n");
    scanf( "%lf", &x_v);
    printf(" \n Please enter initial y velocity of particle \n");
    scanf( "%lf", &y_v);
            
            
            
            
            
            
                            /***********************************
                            +++++++ PART 3 - COMPUTATION +++++++
                            ***********************************/
            
            
    /* Defining position x and y for n=1 */
     x[1]=x[0]+(x_v*dt);
     y[1]=y[0]+(y_v*dt);
    
     for(n=1;n<100000;n++)
    
    /* here is the main, mathematical portion of the program, */
    {
        double dxm = x[n] + 1.0;
        double dxp = x[n] - 1.0;
        double dy = y[n];
        double denom_minus_inv = pow(dxm*dxm + dy*dy, -1.5);
        double denom_plus_inv = pow(dxp*dxp + dy*dy, -1.5);
        
        /* the following expressions correspond to those on the problem sheet and are used to compute accleration 
         in the x-direction and in the y-direction */
        
                a_x[n] = -m_a*dxm*denom_minus_inv - m_b*dxp*denom_plus_inv;
                a_y[n] = -m_a*dy*denom_minus_inv - m_b*dy*denom_plus_inv;
        
        
        /* Next using the value obtained for acceleration, we compute x-position and y-position for each time increment dt */
        
                x[n+1]=((2*x[n])-x[n-1] +(dt*dt*a_x[n]));
                y[n+1]=((2*y[n])-y[n-1]+(dt*dt*a_y[n]));
                time[n+1]=(dt*n);
        
        /* output file formatting may be problematic when computed with certain graphing software (MATLAB would not
         recognise points with negative x values because the minus sign would make the y value into 'NaN')  - although 
         the problem sheet says to seperate the three columns with just a space, I personally used double commas, which
         allowed MATLAB to interpret the three columns correctly (submitted work uses spaces as asked) */
        
        fprintf(output, "%lf,, %lf,, %lf\n", time[n-1], x[n-1], y[n-1]);
        
        
                         /***********************************
                         +++ PART 4 - COLLISION DETECTION +++
                         ***********************************/
        
        

        /* here we set the 'sensitivity' of collision detection, i.e. how close the particle has to
        pass by one of the fixed bodies before it is registered as a collision. I have chosen a value 
        of '0.1' but this remains somewhat large. After a collision we get huge acceleration so I prefer 
        to be conservative about collisions*/
        

                if ((1-sen)<=x[n-1] && x[n-1]<=(1+sen) && (0-sen)<=y[n-1] && y[n-1]<=(0+sen))
                { printf( " \n Collision has been detected with M+ at (1,0) \n");
                    break;
                    break;
                    /* Double break functions used because we need to leave 'if' (collision) loop 
                     and 'for' (next particle) loop */
                }
                
                if ((-1+sen)>=x[n-1] && x[n-1]>=(-1-sen) && (0-sen)<=y[n-1] && y[n-1]<=(0+sen))
                { printf( " \n Collision has been detected with M- at (-1,0) \n");
                    break;
                    break;
                }
                
                /* here we test for collisions with boundaries, this is more easy than for testing 
                 for colisions with the fixed bodies - as soon as the particle leaves the arena */
                
                if (x[n-1]<=-abs(x_boundary))
                { printf( " \n Collision has been detected with user-defined positive x boundary \n");
                    break;
                    break;
                }
                
                if (x[n-1]>=abs(x_boundary))
                { printf( " \n Collision has been detected with user-defined negative x boundary \n");
                    break;
                    break;
                }
                
                if (y[n-1]<=-abs(y_boundary))
                { printf( " \n Collision has been detected with user-defined positive y boundary \n");
                    break;
                    break;
                }
                
                if (y[n-1]>=abs(y_boundary))
                { printf( " \n Collision has been detected with user-defined negative y boundary \n");
                    break;
                    break;
        }
    
    }
}
    
    
    
    
    
                        /***********************************
                        +++++++ PART 5 - END MESSAGE +++++++
                        ************************************/
    
    
                        /* This is the end of the program */
    
    
    printf ("***************** END OF SIMULATION *******************");
    printf (" File outputed as ***'three_body.out'*** in this directory. PLEASE DELETE OR RENAME THIS FILE BEFORE RUNNING A NEW SIMULATION " );
    
            return(0);
}

/* as of 20/01 at 12:13PM compiles with gcc -lm -ansi -Wall -pedantic */
