/*
 * Copyright © 2012, United States Government, as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All rights reserved.
 * 
 * The NASA Tensegrity Robotics Toolkit (NTRT) v1 platform is licensed
 * under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0.
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific language
 * governing permissions and limitations under the License.
*/

#ifndef RP_MODEL_H
#define RP_MODEL_H

/**
 * @file RPModel.h
 * @brief Contains the definition of class RPModel.
 * $Id$
 */

// This library
#include "core/tgModel.h"
#include "core/tgSubject.h"
#include "core/tgRod.h"
#include "core/abstractMarker.h" //##### BCera - Added for later use of abstract markers
#include "examples/learningSpines/BaseSpineModelLearning.h"
// The C++ Standard Library
#include <vector>
#include <iostream>
#include <fstream>

// Forward declarations
class tgBasicActuator;
class tgRod;
class tgNode;
class tgModelVisitor;
class tgStructure;
class tgWorld;


/**
 * Class that creates the six strut "superball" model using tgcreator
 */
class RPModel : public tgSubject<RPModel>, public tgModel
{
public: 
	
	/**
     * The only constructor. Utilizes default constructor of tgModel
     * Configuration parameters are within the .cpp file in this case,
     * not passed in. 
     */
    RPModel();
	
    /**
     * Destructor. Deletes controllers, if any were added during setup.
     * Teardown handles everything else.
     */
    virtual ~RPModel();
    
    /**
     * Create the model. Place the rods and strings into the world
     * that is passed into the simulation. This is triggered
     * automatically when the model is added to the simulation, when
     * tgModel::setup(world) is called (if this model is a child),
     * and when reset is called. Also notifies controllers of setup.
     * @param[in] world - the world we're building into
     */
    virtual void setup(tgWorld& world);
    
    /**
     * Undoes setup. Deletes child models. Called automatically on
     * reset and end of simulation. Notifies controllers of teardown
     */
    void teardown();
    
    /**
     * Step the model, its children. Notifies controllers of step.
     * @param[in] dt, the timestep. Must be positive.
     */
    virtual void step(double dt);
	
	/**
     * Receives a tgModelVisitor and dispatches itself into the
     * visitor's "render" function. This model will go to the default
     * tgModel function, which does nothing.
     * @param[in] r - a tgModelVisitor which will pass this model back
     * to itself 
     */
    virtual void onVisit(tgModelVisitor& r);
    
    /**
     * Return a vector of all muscles for the controllers to work with.
     * @return A vector of all of the muscles
     */
    const std::vector<tgBasicActuator*>& getAllActuators() const;    
    
    
    // Kyunam
    const std::vector<tgRod*>& getAllRods() const;
    
    const std::vector<tgBaseRigid*>& getAllBaseRigids() const;

    //Vince
    const std::vector<abstractMarker*>& getAllAbstractMarkers() const;
   
    //Brian
    int mGrnd[3];
    int toggle,tipFlag;
    std::vector<abstractMarker> markers;
	
private:
	
	/**
     * A function called during setup that determines the positions of
     * the nodes based on construction parameters. Rewrite this function
     * for your own models
     * @param[in] tetra: A tgStructure that we're building into
     */
    void addNodes(tgStructure& s);
	
	/**
     * A function called during setup that creates rods from the
     * relevant nodes. Rewrite this function for your own models.
     * @param[in] s A tgStructure that we're building into
     */
    static void addRods(tgStructure& s);
	
	/**
     * A function called during setup that creates muscles (Strings) from
     * the relevant nodes. Rewrite this function for your own models.
     * @param[in] s A tgStructure that we're building into
     */
    static void addActuators(tgStructure& s);
   
    /**
     * Adds the 12 markers to the end of the rods so that we can visualize
     * them and track their position
     */
    void addMarkers(tgStructure& s);

	/*
	 * Moves all the rods (that are actually all the rigid bodies) according to the arguments.
	 * First rotates the structure around 3 axises given 3 angles.
	 * Moves the structure to the target point.
	 * Sets all the bars speed to the given speed vector.
	 * (muscles and markers are moved automatically since they are attached).
	 */
    
    void findBottomNodes();
      /* Finds lowest three nodes by checking Y values for all 12 nodes (excluding payload)*/

    
 
	
private:
	
	/**
     * A list of all of the muscles. Will be empty until most of the way
     * through setup
     */

    
    std::vector<tgBasicActuator*> allActuators;
    
    std::vector<tgNode*> allNodes;
    
    std::vector<tgRod*> allRods;
    
    std::vector<tgBaseRigid*> allBaseRigids;
    
    std::vector<btVector3> nodePositions;

    std::vector<abstractMarker*> allAbstractMarkers;

    double globalTime, secCount;
    std::ofstream sim_out;
    
};

#endif  // RP_MODEL_H
