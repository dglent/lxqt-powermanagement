/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * LXDE-Qt - a lightweight, Qt based, desktop toolset
 * http://razor-qt.org
 *
 * Copyright: 2012 Razor team
 * Authors:
 *   Christian Surlykke <christian@surlykke.dk>
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */
#include <qt4/QtGui/qcombobox.h>

#include "lidsettings.h"
#include "ui_lidsettings.h"
#include "common.h"

LidSettings::LidSettings(LxQt::Settings *settings, QWidget *parent) :
    QWidget(parent),
    mUi(new Ui::LidSettings),
    mLoading(false)
{
    mSettings = settings;
    mUi->setupUi(this);
    fillComboBox(mUi->onBatteryActionComboBox);
    fillComboBox(mUi->onAcActionComboBox);
    fillComboBox(mUi->extMonOnBatteryActionComboBox);
    fillComboBox(mUi->extMonOnAcActionComboBox);
    connect(mUi->onBatteryActionComboBox, SIGNAL(activated(int)), this, SLOT(saveAction()));
    connect(mUi->onAcActionComboBox, SIGNAL(activated(int)), this, SLOT(saveAction()));
    connect(mUi->extMonOnBatteryActionComboBox, SIGNAL(activated(int)), this, SLOT(saveAction()));
    connect(mUi->extMonOnAcActionComboBox, SIGNAL(activated(int)), this, SLOT(saveAction()));
    connect(mUi->extMonGroupBox, SIGNAL(toggled(bool)), this, SLOT(saveAction()));
}

LidSettings::~LidSettings()
{
    delete mUi;
}

void LidSettings::loadSettings()
{
    loadValueFromSettings(mSettings, mUi->onBatteryActionComboBox, LIDCLOSEDACTION_KEY, 0);
    int fallBackOnAcIfNotDefined = currentValue(mUi->onBatteryActionComboBox);
    loadValueFromSettings(mSettings, mUi->onAcActionComboBox, LIDCLOSED_AC_ACTION_KEY, fallBackOnAcIfNotDefined);
    loadValueFromSettings(mSettings, mUi->extMonOnBatteryActionComboBox, LIDCLOSED_EXT_MON_ACTION_KEY, 0);
    int fallBackExtMonOnAcIfNotDefined = currentValue(mUi->extMonOnBatteryActionComboBox);
    loadValueFromSettings(mSettings, mUi->extMonOnAcActionComboBox, LIDCLOSED_EXT_MON_AC_ACTION_KEY, fallBackExtMonOnAcIfNotDefined);

    mUi->extMonGroupBox->setChecked(mSettings->value(ENABLE_EXT_MON_LIDCLOSED_ACTIONS, false).toBool());
}

void LidSettings::saveAction()
{
    mSettings->setValue(LIDCLOSEDACTION_KEY, currentValue(mUi->onBatteryActionComboBox));
    mSettings->setValue(LIDCLOSED_AC_ACTION_KEY, currentValue(mUi->onAcActionComboBox));
    mSettings->setValue(LIDCLOSED_EXT_MON_ACTION_KEY, currentValue(mUi->extMonOnBatteryActionComboBox));
    mSettings->setValue(LIDCLOSED_EXT_MON_AC_ACTION_KEY, currentValue(mUi->extMonOnAcActionComboBox));
    mSettings->setValue(ENABLE_EXT_MON_LIDCLOSED_ACTIONS, mUi->extMonGroupBox->isChecked());
}
