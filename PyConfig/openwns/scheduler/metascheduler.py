###############################################################################
# This file is part of openWNS (open Wireless Network Simulator)
# _____________________________________________________________________________
#
# Copyright (C) 2004-2007
# Chair of Communication Networks (ComNets)
# Kopernikusstr. 5, D-52074 Aachen, Germany
# phone: ++49-241-80-27910,
# fax: ++49-241-80-22242
# email: info@openwns.org
# www: http://www.openwns.org
# _____________________________________________________________________________
#
# openWNS is free software; you can redistribute it and/or modify it under the
# terms of the GNU Lesser General Public License version 2 as published by the
# Free Software Foundation;
#
# openWNS is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
# A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
# details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
###############################################################################

from openwns.pyconfig import attrsetter
import openwns.logger


######################################################
### MetaScheduler Setup)

class MetaScheduler(object):

    def __init__(self, numberBaseStations):
        self.numberBaseStations = numberBaseStations
       # print "NBS" + str(numberBaseStations)
        #self.logger = openwns.logger.Logger("WNS", "MetaScheduler", True, parentLogger);

class NoMetaScheduler(MetaScheduler):
    plugin = "NoMetaScheduler"
  
    def __init__(self):
	MetaScheduler.__init__(self, 0)

class GreedyMetaScheduler(MetaScheduler):
    plugin = "GreedyMetaScheduler"
  
    def __init__(self):
	MetaScheduler.__init__(self, 0)
