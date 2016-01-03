//
// Created by jakub on 12/29/15.
//

#ifndef BACHELOR_THESIS_NEIGHBOURHOOD_UPDATER_H
#define BACHELOR_THESIS_NEIGHBOURHOOD_UPDATER_H

namespace pso{
    class NeighbourhoodUpdater;
}

/*
 * Pure Abstract class used to provide interface for Neighbourhood update.
 *
 * Classes deriving from this base should implement the update function
 * in order to update the local best position of each particle
 */
class pso::NeighbourhoodUpdater {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

public:
    NeighbourhoodUpdater();

    virtual ~NeighbourhoodUpdater();

    virtual void update() = 0;
};


#endif //BACHELOR_THESIS_NEIGHBOURHOOD_UPDATER_H
