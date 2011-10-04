/**
 * The Shadow Simulator
 *
 * Copyright (c) 2010-2011 Rob Jansen <jansen@cs.umn.edu>
 *
 * This file is part of Shadow.
 *
 * Shadow is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Shadow is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Shadow.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <glib.h>
#include "shadow.h"

EventVTable spin_vtable = {
	(EventExecuteFunc)spin_execute,
	(EventFreeFunc)spin_free,
	MAGIC_VALUE
};

SpinEvent* spin_new(guint seconds) {
	SpinEvent* event = g_new(SpinEvent, 1);
	MAGIC_INIT(event);

	event_init(&(event->super), &spin_vtable);
	event->spin_seconds = seconds;

	return event;
}

void spin_free(SpinEvent* event) {
	MAGIC_ASSERT(event);
	MAGIC_CLEAR(event);
	g_free(event);
}

void spin_execute(SpinEvent* event) {
	MAGIC_ASSERT(event);

	debug("executing spin event for %u seconds", event->spin_seconds);

	guint64 i = 100000000 * event->spin_seconds;
	while(i--) {
		continue;
	}

	SpinEvent* se = spin_new(event->spin_seconds);
	SimulationTime t = event->spin_seconds * SIMTIME_ONE_SECOND;
	worker_scheduleEvent((Event*)se, t);
}
