/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/Interface/Interface.h>
#include <AzCore/Serialization/SerializeContext.h>

class QToolBar;

namespace AzToolsFramework
{
    using ToolBarManagerOperationResult = AZ::Outcome<void, AZStd::string>;
    using ToolBarManagerIntegerResult = AZ::Outcome<int, AZStd::string>;

    //! Provides additional properties to initialize a ToolBar upon registration.
    struct ToolBarProperties
    {
        AZ_RTTI(ToolBarProperties, "{49B21EA2-5449-47EC-AEFC-3DBC0288CED0}");

        ToolBarProperties() = default;
        virtual ~ToolBarProperties() = default;

        AZStd::string m_name = "";
    };

    //! ToolBarManagerInterface
    //! Interface to register and manage ToolBars in the Editor.
    class ToolBarManagerInterface
    {
    public:
        AZ_RTTI(ToolBarManagerInterface, "{2736A3CA-B260-4355-B61D-E287A3DB2A6F}");

        //! Register a new ToolBar to the ToolBar Manager.
        //! @param toolBarIdentifier The identifier for the ToolBar that is being registered.
        //! @param properties The properties object for the newly registered ToolBar.
        //! @return A successful outcome object, or a string with a message detailing the error in case of failure.
        virtual ToolBarManagerOperationResult RegisterToolBar(const AZStd::string& toolBarIdentifier, const ToolBarProperties& properties) = 0;

        //! Bind an Action to a ToolBar.
        //! @param toolBarIdentifier The identifier for the ToolBar the action is being added to.
        //! @param actionIdentifier The identifier for the action to add to the ToolBar.
        //! @param sortIndex An integer defining the position the action should appear in the ToolBar.
        //! @return A successful outcome object, or a string with a message detailing the error in case of failure.
        virtual ToolBarManagerOperationResult AddActionToToolBar(
            const AZStd::string& toolBarIdentifier, const AZStd::string& actionIdentifier, int sortIndex) = 0;

        //! Add a Separator to a ToolBar.
        //! @param toolBarIdentifier The identifier for the ToolBar the separator is being added to.
        //! @param sortIndex An integer defining the position the separator should appear in the ToolBar.
        //! @return A successful outcome object, or a string with a message detailing the error in case of failure.
        virtual ToolBarManagerOperationResult AddSeparatorToToolBar(
            const AZStd::string& toolBarIdentifier, int sortIndex) = 0;

        //! Retrieve a QToolBar from its identifier.
        //! @param toolBarIdentifier The identifier for the ToolBar to retrieve.
        //! @return A raw pointer to the QToolBar object.
        virtual QToolBar* GetToolBar(const AZStd::string& toolBarIdentifier) = 0;

        //! Retrieve the sort key of an action in a toolbar from its identifier.
        //! @param toolBarIdentifier The identifier for the toolbar to query.
        //! @param actionIdentifier The identifier for the action whose sort key to get in the toolbar.
        //! @return A successful outcome object containing the sort key, or a string with a message detailing the error in case of failure.
        virtual ToolBarManagerIntegerResult GetSortKeyOfActionInToolBar(const AZStd::string& toolBarIdentifier, const AZStd::string& actionIdentifier) const = 0;
    };

} // namespace AzToolsFramework
