#ifndef PERSISTENCE_CLIENT_LIBRARY_LC_INTERFACE_H
#define PERSISTENCE_CLIENT_LIBRARY_LC_INTERFACE_H

/******************************************************************************
 * Project         Persistency
 * (c) copyright   2012
 * Company         XS Embedded GmbH
 *****************************************************************************/
/******************************************************************************
   Permission is hereby granted, free of charge, to any person obtaining
   a copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
   DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
   TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
   OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
******************************************************************************/
 /**
 * @file           persistence_client_library_lc_interface.h
 * @ingroup        Persistence client library
 * @author         Ingo Huerner
 * @brief          Implementation of the persistence client library lifecycle interface.
 * @see
 */

#include <dbus/dbus.h>


/**
 * @brief Check if a com.contiautomotive.NodeStateManager.LifecycleConsumer message has been received
 *
 * @param connection the debus connection
 * @param message the dbus message
 * @param user_data data handed over to this function
 *
 * @return DBUS_HANDLER_RESULT_HANDLED or DBUS_HANDLER_RESULT_NOT_YET_HANDLED
 */
DBusHandlerResult checkLifecycleMsg(DBusConnection * connection, DBusMessage * message, void * user_data);


/**
 * @brief send register message 'RegisterShutdownClient' to com.contiautomotive.NodeStateManager.Consumer
 *
 * @return 0 on success or -1 on error
 */
int register_lifecycle();


/**
 * @brief send register message 'UnRegisterShutdownClient' to com.contiautomotive.NodeStateManager.Consumer
 *
 * @return 0 on success or -1 on error
 */
int unregister_lifecycle();


/**
 * @brief process a shutdown message (close all open files, open databases, ...
 *
 * @param requestId the requestID
 */
void process_prepare_shutdown(unsigned char requestId);



#endif /* PERSISTENCE_CLIENT_LIBRARY_LC_INTERFACE_H */
