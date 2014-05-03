/*
    MIDI Virtual Piano Keyboard
    Copyright (C) 2008-2010, Pedro Lopez-Cabanillas <plcl@users.sf.net>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; wint nInPorts = m_midiin->getPortCount();
//        if (nInPorts == 0) {
//            delete m_midiin;
//            m_midiin = NULL;
//        }ithout even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; If not, see <http://www.gnu.org/licenses/>.
*/

#include "vpiano.h"
//#include "instrument.h"
#include "mididefs.h"
//#include "knob.h"
//#include "classicstyle.h"
#include "RtMidi.h"
//#include "constants.h"
//#include "riffimportdlg.h"
//#include "extracontrols.h"
//#include "about.h"
//#include "preferences.h"
//#include "midisetup.h"
//#include "kmapdialog.h"
//#include "events.h"

//#if ENABLE_DBUS
//#include "vmpk_adaptor.h"
//#include <QtDBus/QDBusConnection>
//#endif
//
//#include <QtGui/QDesktopServices>
//#include <QtGui/QInputDialog>
//#include <QtGui/QFileDialog>
//#include <QtGui/QMessageBox>
//#include <QtGui/QApplication>
//#include <QtGui/QCloseEvent>
//#include <QtGui/QComboBox>
//#include <QtGui/QSlider>
//#include <QtGui/QSpinBox>
//#include <QtGui/QDial>
//#include <QtGui/QToolButton>
//#include <QtGui/QToolTip>
//#include <QtCore/QUrl>
//#include <QtCore/QString>
//#include <QtCore/QSettings>
//#include <QtCore/QDebug>

VPiano::VPiano()
//      m_midiout(0),
//    m_midiin(0),
//    m_currentOut(-1),
//    m_currentIn(-1),
//    m_inputActive(false),
//    m_midiThru(false),
//    m_initialized(false),
//    m_dlgAbout(NULL),
//    m_dlgPreferences(NULL),
//    m_dlgMidiSetup(NULL),
//    m_dlgKeyMap(NULL),
//    m_dlgExtra(NULL),
//    m_dlgRiffImport(NULL)
{
//#if ENABLE_DBUS
//    new VmpkAdaptor(this);
//    QDBusConnection dbus = QDBusConnection::sessionBus();
//    dbus.registerObject("/", this);
//    dbus.registerService("net.sourceforge.vmpk");
//#endif
//    ui.setupUi(this);
//    ui.actionStatusBar->setChecked(false);
//    connect(ui.actionAbout, SIGNAL(triggered()), SLOT(slotAbout()));
//    connect(ui.actionAbout_Qt, SIGNAL(triggered()), SLOT(slotAboutQt()));
//    connect(ui.actionConnections, SIGNAL(triggered()), SLOT(slotConnections()));
//    connect(ui.actionPreferences, SIGNAL(triggered()), SLOT(slotPreferences()));
//    connect(ui.actionEditKM, SIGNAL(triggered()), SLOT(slotEditKeyboardMap()));
//    connect(ui.actionContents, SIGNAL(triggered()), SLOT(slotHelpContents()));
//    connect(ui.actionWebSite, SIGNAL(triggered()), SLOT(slotOpenWebSite()));
//    connect(ui.actionImportSoundFont, SIGNAL(triggered()), SLOT(slotImportSF()));
//    connect(ui.actionEditExtraControls, SIGNAL(triggered()), SLOT(slotEditExtraControls()));
//    connect(ui.actionNoteNames, SIGNAL(triggered()), SLOT(slotShowNoteNames()));
//    ui.pianokeybd->setPianoHandler(this);
//    initialization();
}

VPiano::~VPiano()
{
    try {
        if (this->m_midiout != NULL) {
            m_midiout->closePort();
            delete m_midiout;
            m_midiout = 0;
        }
//        if (m_midiin != NULL) {
//            if (m_inputActive) {
//                m_midiin->cancelCallback();
//                m_inputActive = false;
//            }
//            if (m_currentIn > -1)
//                m_midiin->closePort();
//            delete m_midiin;
//        }
    } catch (RtError& err) {
        printf("things went south in the destructor");
        //qWarning() << QString::fromStdString(err.getMessage());
        return;
    }
    //exit();
    return;
}

//void VPiano::initialization()
//{
//    if ((m_initialized = initMidi())) {
//        refreshConnections();
//        readSettings();
//        initToolBars();
//        applyPreferences();
//        applyConnections();
//        applyInitialSettings();
//        initExtraControllers();
//    }
//}

int VPiano::getInputChannel()
{
    return m_channel;
}

//void midiCallback( double /*deltatime*/,
//                   std::vector< unsigned char > *message,
//                   void *userData )
//{
//    QEvent* ev = NULL;
//    VPiano* instance = static_cast<VPiano*>(userData);
//    instance->midiThru(message);
//    unsigned char status = message->at(0) & MASK_STATUS;
//    unsigned char channel = message->at(0) & MASK_CHANNEL;
//    unsigned char channelFilter = instance->getInputChannel();
//    if (channel == channelFilter) {
//        switch( status ) {
//        case STATUS_NOTEOFF:
//        case STATUS_NOTEON: {
//                unsigned char midi_note = message->at(1);
//                unsigned char vel = message->at(2);
//                if ((status == STATUS_NOTEOFF) || (vel == 0))
//                    ev = new NoteOffEvent(midi_note);
//                else
//                    ev = new NoteOnEvent(midi_note);
//            }
//            break;
//        case STATUS_POLYAFT: {
//                unsigned char note = message->at(1);
//                unsigned char value = message->at(2);
//                ev = new PolyKeyPressEvent(note, value);
//            }
//            break;
//        case STATUS_CTLCHG: {
//                unsigned char ctl = message->at(1);
//                unsigned char val = message->at(2);
//                ev = new ControlChangeEvent(ctl, val);
//            }
//            break;
//        case STATUS_PROGRAM: {
//                unsigned char value = message->at(1);
//                ev = new ProgramChangeEvent(value);
//            }
//            break;
//        case STATUS_CHANAFT: {
//                unsigned char value = message->at(1);
//                ev = new ChannelKeyPressEvent(value);
//            }
//            break;
//        case STATUS_BENDER: {
//                int value = (message->at(1) + 0x80 * message->at(2)) - BENDER_MID;
//                ev = new PitchWheelEvent(value);
//            }
//            break;
//        }
//    }
//    if (ev != NULL)
//        QApplication::postEvent(instance, ev);
//}

bool VPiano::initMidi()
{
    try {
        m_midiout = new RtMidiOut("TouchMIDI");//QSTR_VMPKOUTPUT.toStdString());
       // m_midiin = new RtMidiIn("in");//QSTR_VMPKINPUT.toStdString());
#if !defined(__LINUX_ALSASEQ__) && !defined(__MACOSX_CORE__)
        int nOutPorts = m_midiout->getPortCount();
        if (nOutPorts == 0) {
            delete m_midiout;
            m_midiout = 0;
            //QMessageBox::critical( this, tr("Error"),
                printf("No MIDI output ports available. Aborting\n");
            return false;
        }
//        int nInPorts = m_midiin->getPortCount();
//        if (nInPorts == 0) {
//            delete m_midiin;
//            m_midiin = NULL;
//        }
#endif
#if defined(__LINUX_ALSASEQ__) || defined(__MACOSX_CORE__)
        if (m_midiout != NULL)
            m_midiout->openVirtualPort("vout");
        //if (m_midiin != NULL)
          //  m_midiin->openVirtualPort("vin");//QSTR_VMPKINPUT.toStdString());
#else //if defined(__WINDOWS_MM__) || defined(__IRIX_MD__)
        m_midiout->openPort( m_currentOut = 0 );
#endif
//        if (m_midiin != NULL) {
//            // ignore SYX, clock and active sense
//            m_midiin->ignoreTypes(true,true,true);
//            //m_midiin->setCallback( &midiCallback, this );//I think this is only for midi into the program
//            m_inputActive = true;
//        }
    } catch (RtError& err) {
        printf("Something went south in initMIDI\n");
//        QMessageBox::critical( this, tr("Error. Aborting"),
//                               QString::fromStdString(err.getMessage()));
        return false;
    }
    return true;
}

//void VPiano::initToolBars()
//{
//    QLabel *lbl;
//    m_dialStyle = new ClassicStyle();
//    m_dialStyle->setParent(this);
//    // Notes tool bar
//    ui.toolBarNotes->addWidget(lbl = new QLabel(tr("Channel:"), this));
//    lbl->setMargin(TOOLBARLABELMARGIN);
//    m_sboxChannel = new QSpinBox(this);
//    m_sboxChannel->setMinimum(1);
//    m_sboxChannel->setMaximum(MIDICHANNELS);
//    m_sboxChannel->setValue(m_channel + 1);
//    m_sboxChannel->setFocusPolicy(Qt::NoFocus);
//    ui.toolBarNotes->addWidget(m_sboxChannel);
//    ui.toolBarNotes->addWidget(lbl = new QLabel(tr("Base Octave:"), this));
//    lbl->setMargin(TOOLBARLABELMARGIN);
//    m_sboxOctave = new QSpinBox(this);
//    m_sboxOctave->setMinimum(0);
//    m_sboxOctave->setMaximum(9);
//    m_sboxOctave->setValue(m_baseOctave);
//    m_sboxOctave->setFocusPolicy(Qt::NoFocus);
//    ui.toolBarNotes->addWidget(m_sboxOctave);
//    ui.toolBarNotes->addWidget(lbl = new QLabel(tr("Transpose:"), this));
//    lbl->setMargin(TOOLBARLABELMARGIN);
//    m_sboxTranspose = new QSpinBox(this);
//    m_sboxTranspose->setMinimum(-11);
//    m_sboxTranspose->setMaximum(11);
//    m_sboxTranspose->setValue(m_transpose);
//    m_sboxTranspose->setFocusPolicy(Qt::NoFocus);
//    ui.toolBarNotes->addWidget(m_sboxTranspose);
//    ui.toolBarNotes->addWidget(lbl = new QLabel(tr("Velocity:"), this));
//    lbl->setMargin(TOOLBARLABELMARGIN);
//    m_Velocity = new Knob(this);
//    m_Velocity->setFixedSize(32, 32);
//    m_Velocity->setStyle(dlgPreferences()->getStyledWidgets()? m_dialStyle : 0);
//    m_Velocity->setMinimum(0);
//    m_Velocity->setMaximum(127);
//    m_Velocity->setDefaultValue(100);
//    m_Velocity->setDialMode(Knob::LinearMode);
//    m_Velocity->setValue(m_velocity);
//    m_Velocity->setToolTip(QString::number(m_velocity));
//    m_Velocity->setFocusPolicy(Qt::NoFocus);
//    ui.toolBarNotes->addWidget(m_Velocity);
//    connect( m_sboxChannel, SIGNAL(valueChanged(int)),
//             SLOT(slotChannelValueChanged(int)) );
//    connect( m_sboxOctave, SIGNAL(valueChanged(int)),
//             SLOT(slotBaseOctaveValueChanged(int)) );
//    connect( m_sboxTranspose, SIGNAL(valueChanged(int)),
//             SLOT(slotTransposeValueChanged(int)) );
//    connect( m_Velocity, SIGNAL(valueChanged(int)),
//             SLOT(slotVelocityValueChanged(int)) );
//    // Controllers tool bar
//    ui.toolBarControllers->addWidget(lbl = new QLabel(tr("Control:"), this));
//    lbl->setMargin(TOOLBARLABELMARGIN);
//    m_comboControl = new QComboBox(this);
//    m_comboControl->setSizeAdjustPolicy(QComboBox::AdjustToContents);
//    m_comboControl->setFocusPolicy(Qt::NoFocus);
//    ui.toolBarControllers->addWidget(m_comboControl);
//    ui.toolBarControllers->addWidget(lbl = new QLabel(tr("Value:"), this));
//    lbl->setMargin(TOOLBARLABELMARGIN);
//    m_Control= new Knob(this);
//    m_Control->setFixedSize(32, 32);
//    m_Control->setStyle(dlgPreferences()->getStyledWidgets()? m_dialStyle : 0);
//    m_Control->setMinimum(0);
//    m_Control->setMaximum(127);
//    m_Control->setValue(0);
//    m_Control->setToolTip("0");
//    m_Control->setDefaultValue(0);
//    m_Control->setDialMode(Knob::LinearMode);
//    m_Control->setFocusPolicy(Qt::NoFocus);
//    ui.toolBarControllers->addWidget(m_Control);
//    connect( m_comboControl, SIGNAL(currentIndexChanged(int)),
//             SLOT(slotComboControlCurrentIndexChanged(int)) );
//    connect( m_Control, SIGNAL(sliderMoved(int)),
//             SLOT(slotControlSliderMoved(int)) );
//    // Pitch bender tool bar
//    ui.toolBarBender->addWidget(lbl = new QLabel(tr("Bender:"), this));
//    lbl->setMargin(TOOLBARLABELMARGIN);
//    m_bender = new QSlider(this);
//    m_bender->setOrientation(Qt::Horizontal);
//    m_bender->setMaximumWidth(200);
//    m_bender->setMinimum(BENDER_MIN);
//    m_bender->setMaximum(BENDER_MAX);
//    m_bender->setValue(0);
//    m_bender->setToolTip("0");
//    m_bender->setFocusPolicy(Qt::NoFocus);
//    ui.toolBarBender->addWidget(m_bender);
//    connect( m_bender, SIGNAL(sliderMoved(int)),
//             SLOT(slotBenderSliderMoved(int)) );
//    connect( m_bender, SIGNAL(sliderReleased()),
//             SLOT(slotBenderSliderReleased()) );
//    // Programs tool bar
//    ui.toolBarPrograms->addWidget(lbl = new QLabel(tr("Bank:"), this));
//    lbl->setMargin(TOOLBARLABELMARGIN);
//    m_comboBank = new QComboBox(this);
//    m_comboBank->setSizeAdjustPolicy(QComboBox::AdjustToContents);
//    m_comboBank->setFocusPolicy(Qt::NoFocus);
//    ui.toolBarPrograms->addWidget(m_comboBank);
//    ui.toolBarPrograms->addWidget(lbl = new QLabel(tr("Program:"), this));
//    lbl->setMargin(TOOLBARLABELMARGIN);
//    m_comboProg = new QComboBox(this);
//    m_comboProg->setSizeAdjustPolicy(QComboBox::AdjustToContents);
//    m_comboProg->setFocusPolicy(Qt::NoFocus);
//    ui.toolBarPrograms->addWidget(m_comboProg);
//    connect( m_comboBank, SIGNAL(activated(int)),
//             SLOT(slotComboBankActivated(int)) );
//    connect( m_comboProg, SIGNAL(activated(int)),
//             SLOT(slotComboProgActivated(int)) );
//    // Toolbars actions: toggle view
//    connect(ui.toolBarNotes->toggleViewAction(), SIGNAL(toggled(bool)),
//            ui.actionNotes, SLOT(setChecked(bool)));
//    connect(ui.toolBarControllers->toggleViewAction(), SIGNAL(toggled(bool)),
//            ui.actionControllers, SLOT(setChecked(bool)));
//    connect(ui.toolBarBender->toggleViewAction(), SIGNAL(toggled(bool)),
//            ui.actionBender, SLOT(setChecked(bool)));
//    connect(ui.toolBarPrograms->toggleViewAction(), SIGNAL(toggled(bool)),
//            ui.actionPrograms, SLOT(setChecked(bool)));
//    connect(ui.toolBarExtra->toggleViewAction(), SIGNAL(toggled(bool)),
//            ui.actionExtraControls, SLOT(setChecked(bool)));
//    // Toolbars actions: buttons
//    connect( ui.actionPanic, SIGNAL(triggered()),
//             SLOT(slotPanic()));
//    connect( ui.actionResetAll, SIGNAL(triggered()),
//             SLOT(slotResetAllControllers()));
//    connect( ui.actionReset, SIGNAL(triggered()),
//             SLOT(slotResetBender()));
//    connect( ui.actionEditExtra, SIGNAL(triggered()),
//             SLOT(slotEditExtraControls()));
//    /* connect( ui.actionEditPrograms, SIGNAL(triggered()),
//             SLOT(slotEditPrograms())); */
//}

//void VPiano::slotDebugDestroyed(QObject *obj)
//{
//    qDebug() << Q_FUNC_INFO << obj->metaObject()->className();
//}
//
//void VPiano::clearExtraControllers()
//{
//    QList<QAction*> allActs = ui.toolBarExtra->actions();
//    foreach(QAction* a, allActs) {
//        if (a != ui.actionEditExtra) {
//            ui.toolBarExtra->removeAction(a);
//            delete a;
//        }
//    }
//    ui.toolBarExtra->clear();
//    ui.toolBarExtra->addAction(ui.actionEditExtra);
//    ui.toolBarExtra->addSeparator();
//}
//
//QByteArray VPiano::readSysexDataFile(const QString& fileName)
//{
//    QFile file(fileName);
//    file.open(QIODevice::ReadOnly);
//    QByteArray res = file.readAll();
//    file.close();
//    return res;
//}
//
//void VPiano::initExtraControllers()
//{
//    QWidget *w = NULL;
//    QCheckBox *chkbox = NULL;
//    Knob *knob = NULL;
//    QSpinBox *spin = NULL;
//    QSlider *slider = NULL;
//    QToolButton *button = NULL;
//    foreach(const QString& s, m_extraControls) {
//        QString lbl;
//        int control = 0;
//        int type = 0;
//        int minValue = 0;
//        int maxValue = 127;
//        int defValue = 0;
//        int value = 0;
//        int size = 100;
//        QString fileName;
//        ExtraControl::decodeString( s, lbl, control, type,
//                                    minValue, maxValue, defValue,
//                                    size, fileName );
//        if (m_ctlState[m_channel].contains(control))
//            value = m_ctlState[m_channel][control];
//        else
//            value = defValue;
//        switch(type) {
//        case 0:
//            chkbox = new QCheckBox(this);
//            chkbox->setStyle(dlgPreferences()->getStyledWidgets() ? m_dialStyle : NULL);
//            chkbox->setProperty(MIDICTLONVALUE, maxValue);
//            chkbox->setProperty(MIDICTLOFFVALUE, minValue);
//            chkbox->setChecked(bool(value));
//            connect(chkbox, SIGNAL(clicked(bool)), SLOT(slotControlClicked(bool)));
//            w = chkbox;
//            break;
//        case 1:
//            knob = new Knob(this);
//            knob->setFixedSize(32, 32);
//            knob->setStyle(dlgPreferences()->getStyledWidgets() ? m_dialStyle : NULL);
//            knob->setMinimum(minValue);
//            knob->setMaximum(maxValue);
//            knob->setValue(value);
//            knob->setToolTip(QString::number(value));
//            knob->setDefaultValue(defValue);
//            knob->setDialMode(Knob::LinearMode);
//            connect(knob, SIGNAL(sliderMoved(int)), SLOT(slotExtraController(int)));
//            w = knob;
//            break;
//        case 2:
//            spin = new QSpinBox(this);
//            spin->setMinimum(minValue);
//            spin->setMaximum(maxValue);
//            spin->setValue(value);
//            connect(spin, SIGNAL(valueChanged(int)), SLOT(slotExtraController(int)));
//            w = spin;
//            break;
//        case 3:
//            slider = new QSlider(this);
//            slider->setOrientation(Qt::Horizontal);
//            slider->setFixedWidth(size);
//            slider->setMinimum(minValue);
//            slider->setMaximum(maxValue);
//            slider->setToolTip(QString::number(value));
//            slider->setValue(value);
//            connect(slider, SIGNAL(sliderMoved(int)), SLOT(slotExtraController(int)));
//            w = slider;
//            break;
//        case 4:
//            button = new QToolButton(this);
//            button->setText(lbl);
//            button->setProperty(MIDICTLONVALUE, maxValue);
//            button->setProperty(MIDICTLOFFVALUE, minValue);
//            connect(button, SIGNAL(clicked(bool)), SLOT(slotControlClicked(bool)));
//            w = button;
//            break;
//        case 5:
//            control = 255;
//            button = new QToolButton(this);
//            button->setText(lbl);
//            button->setProperty(SYSEXFILENAME, fileName);
//            button->setProperty(SYSEXFILEDATA, readSysexDataFile(fileName));
//            connect(button, SIGNAL(clicked(bool)), SLOT(slotControlClicked(bool)));
//            w = button;
//            break;
//        default:
//            w = NULL;
//        }
//        if (w != NULL) {
//            if (!lbl.isEmpty() && type < 4) {
//                QLabel *qlbl = new QLabel(lbl, this);
//                qlbl->setMargin(TOOLBARLABELMARGIN);
//                ui.toolBarExtra->addWidget(qlbl);
//                //connect(qlbl, SIGNAL(destroyed(QObject*)), SLOT(slotDebugDestroyed(QObject*)));
//            }
//            w->setProperty(MIDICTLNUMBER, control);
//            w->setFocusPolicy(Qt::NoFocus);
//            ui.toolBarExtra->addWidget(w);
//            //connect(w, SIGNAL(destroyed(QObject*)), SLOT(slotDebugDestroyed(QObject*)));
//        }
//    }
//}
//
//void VPiano::readSettings()
//{
//    QSettings settings;
//    settings.beginGroup(QSTR_WINDOW);
//    restoreGeometry(settings.value(QSTR_GEOMETRY).toByteArray());
//    restoreState(settings.value(QSTR_STATE).toByteArray());
//    settings.endGroup();
//
//    settings.beginGroup(QSTR_PREFERENCES);
//    m_channel = settings.value(QSTR_CHANNEL, 0).toInt();
//    m_velocity = settings.value(QSTR_VELOCITY, 100).toInt();
//    m_baseOctave = settings.value(QSTR_BASEOCTAVE, 3).toInt();
//    m_transpose = settings.value(QSTR_TRANSPOSE, 0).toInt();
//    int num_octaves = settings.value(QSTR_NUMOCTAVES, 5).toInt();
//    QString insFileName = settings.value(QSTR_INSTRUMENTSDEFINITION).toString();
//    QString insName = settings.value(QSTR_INSTRUMENTNAME).toString();
//    QColor keyColor = settings.value(QSTR_KEYPRESSEDCOLOR, QColor()).value<QColor>();
//    bool grabKb = settings.value(QSTR_GRABKB, false).toBool();
//    bool styledKnobs = settings.value(QSTR_STYLEDKNOBS, true).toBool();
//    bool alwaysOnTop = settings.value(QSTR_ALWAYSONTOP, false).toBool();
//    bool showNames = settings.value(QSTR_SHOWNOTENAMES, false).toBool();
//    int drumsChannel = settings.value(QSTR_DRUMSCHANNEL, MIDIGMDRUMSCHANNEL).toInt();
//    settings.endGroup();
//
//    dlgPreferences()->setNumOctaves(num_octaves);
//    dlgPreferences()->setDrumsChannel(drumsChannel);
//    dlgPreferences()->setKeyPressedColor(keyColor);
//    dlgPreferences()->setGrabKeyboard(grabKb);
//    dlgPreferences()->setStyledWidgets(styledKnobs);
//    dlgPreferences()->setAlwaysOnTop(alwaysOnTop);
//    ui.actionNoteNames->setChecked(showNames);
//    slotShowNoteNames();
//    if (!insFileName.isEmpty()) {
//        dlgPreferences()->setInstrumentsFileName(insFileName);
//        if (!insName.isEmpty()) {
//            dlgPreferences()->setInstrumentName(insName);
//        }
//    }
//
//    settings.beginGroup(QSTR_CONNECTIONS);
//    bool inEnabled = settings.value(QSTR_INENABLED, true).toBool();
//    bool thruEnabled = settings.value(QSTR_THRUENABLED, false).toBool();
//    QString in_port = settings.value(QSTR_INPORT).toString();
//    QString out_port = settings.value(QSTR_OUTPORT).toString();
//    settings.endGroup();
//#if defined(__LINUX_ALSASEQ__) || defined(__MACOSX_CORE__)
//    inEnabled = true;
//#endif
//
//    if (m_midiin == NULL) {
//        dlgMidiSetup()->inputNotAvailable();
//    } else {
//        dlgMidiSetup()->setInputEnabled(inEnabled);
//        dlgMidiSetup()->setThruEnabled(thruEnabled);
//        dlgMidiSetup()->setCurrentInput(in_port);
//    }
//    dlgMidiSetup()->setCurrentOutput(out_port);
//
//    settings.beginGroup(QSTR_KEYBOARD);
//    bool rawKeyboard = settings.value(QSTR_RAWKEYBOARDMODE, false).toBool();
//    QString mapFile = settings.value(QSTR_MAPFILE, QSTR_DEFAULT).toString();
//    QString rawMapFile = settings.value(QSTR_RAWMAPFILE, QSTR_DEFAULT).toString();
//    settings.endGroup();
//    dlgPreferences()->setRawKeyboard(rawKeyboard);
//
//    for (int chan=0; chan<MIDICHANNELS; ++chan) {
//        QString group = QSTR_INSTRUMENT + QString::number(chan);
//        settings.beginGroup(group);
//        m_lastBank[chan] = settings.value(QSTR_BANK, -1).toInt();
//        m_lastProg[chan] = settings.value(QSTR_PROGRAM, 0).toInt();
//        m_lastCtl[chan] = settings.value(QSTR_CONTROLLER, 1).toInt();
//        settings.endGroup();
//
//        group = QSTR_CONTROLLERS + QString::number(chan);
//        settings.beginGroup(group);
//        foreach(const QString& key, settings.allKeys()) {
//            int ctl = key.toInt();
//            int val = settings.value(key, 0).toInt();
//            m_ctlSettings[chan][ctl] = val;
//        }
//        settings.endGroup();
//    }
//
//    settings.beginGroup(QSTR_EXTRACONTROLLERS);
//    m_extraControls.clear();
//    QStringList keys = settings.allKeys();
//    keys.sort();
//    foreach(const QString& key, keys) {
//        m_extraControls << settings.value(key, QString()).toString();
//    }
//    settings.endGroup();
//
//    ui.pianokeybd->getKeyboardMap()->setRawMode(false);
//    ui.pianokeybd->getRawKeyboardMap()->setRawMode(true);
//    if (!mapFile.isEmpty() && mapFile != QSTR_DEFAULT) {
//        dlgPreferences()->setKeyMapFileName(mapFile);
//        ui.pianokeybd->setKeyboardMap(dlgPreferences()->getKeyboardMap());
//    }
//    if (!rawMapFile.isEmpty() && rawMapFile != QSTR_DEFAULT) {
//        dlgPreferences()->setRawKeyMapFileName(rawMapFile);
//        ui.pianokeybd->setRawKeyboardMap(dlgPreferences()->getKeyboardMap());
//    }
//}
//
//void VPiano::writeSettings()
//{
//    QSettings settings;
//    settings.clear();
//
//    settings.beginGroup(QSTR_WINDOW);
//    settings.setValue(QSTR_GEOMETRY, saveGeometry());
//    settings.setValue(QSTR_STATE, saveState());
//    settings.endGroup();
//
//    settings.beginGroup(QSTR_PREFERENCES);
//    settings.setValue(QSTR_CHANNEL, m_channel);
//    settings.setValue(QSTR_VELOCITY, m_velocity);
//    settings.setValue(QSTR_BASEOCTAVE, m_baseOctave);
//    settings.setValue(QSTR_TRANSPOSE, m_transpose);
//    settings.setValue(QSTR_NUMOCTAVES, dlgPreferences()->getNumOctaves());
//    settings.setValue(QSTR_INSTRUMENTSDEFINITION, dlgPreferences()->getInstrumentsFileName());
//    settings.setValue(QSTR_INSTRUMENTNAME, dlgPreferences()->getInstrumentName());
//    settings.setValue(QSTR_KEYPRESSEDCOLOR, dlgPreferences()->getKeyPressedColor());
//    settings.setValue(QSTR_GRABKB, dlgPreferences()->getGrabKeyboard());
//    settings.setValue(QSTR_STYLEDKNOBS, dlgPreferences()->getStyledWidgets());
//    settings.setValue(QSTR_ALWAYSONTOP, dlgPreferences()->getAlwaysOnTop());
//    settings.setValue(QSTR_SHOWNOTENAMES, ui.actionNoteNames->isChecked());
//    settings.setValue(QSTR_DRUMSCHANNEL, dlgPreferences()->getDrumsChannel());
//    settings.endGroup();
//
//    settings.beginGroup(QSTR_CONNECTIONS);
//    settings.setValue(QSTR_INENABLED, dlgMidiSetup()->inputIsEnabled());
//    settings.setValue(QSTR_THRUENABLED, dlgMidiSetup()->thruIsEnabled());
//    settings.setValue(QSTR_INPORT,  dlgMidiSetup()->selectedInputName());
//    settings.setValue(QSTR_OUTPORT, dlgMidiSetup()->selectedOutputName());
//    settings.endGroup();
//
//    settings.beginGroup(QSTR_KEYBOARD);
//    settings.setValue(QSTR_RAWKEYBOARDMODE, dlgPreferences()->getRawKeyboard());
//    settings.setValue(QSTR_MAPFILE, ui.pianokeybd->getKeyboardMap()->getFileName());
//    settings.setValue(QSTR_RAWMAPFILE, ui.pianokeybd->getRawKeyboardMap()->getFileName());
//    settings.endGroup();
//
//    for (int chan=0; chan<MIDICHANNELS; ++chan) {
//
//        QString group = QSTR_CONTROLLERS + QString::number(chan);
//        settings.beginGroup(group);
//        QMap<int,int>::const_iterator it, end;
//        it = m_ctlState[chan].constBegin();
//        end = m_ctlState[chan].constEnd();
//        for (; it != end; ++it)
//            settings.setValue(QString::number(it.key()), it.value());
//        settings.endGroup();
//
//        group = QSTR_INSTRUMENT + QString::number(chan);
//        settings.beginGroup(group);
//        settings.setValue(QSTR_BANK, m_lastBank[chan]);
//        settings.setValue(QSTR_PROGRAM, m_lastProg[chan]);
//        settings.setValue(QSTR_CONTROLLER, m_lastCtl[chan]);
//        settings.endGroup();
//    }
//
//    settings.beginGroup(QSTR_EXTRACONTROLLERS);
//    int i = 0;
//    foreach(const QString& ctl, m_extraControls)  {
//        QString key = QString("%1").arg(i++, 2, 10, QChar('0'));
//        settings.setValue(key, ctl);
//    }
//    settings.endGroup();
//
//    settings.sync();
//}

//void VPiano::closeEvent( QCloseEvent *event )
//{
//    if (m_initialized)
//        writeSettings();
//    event->accept();
//}
//
//void VPiano::customEvent ( QEvent *event )
//{
//    if ( event->type() == NoteOnEventType ) {
//        NoteOnEvent *ev = static_cast<NoteOnEvent*>(event);
//        int n = ev->getNote();
//        ui.pianokeybd->showNoteOn(n);
//#ifdef ENABLE_DBUS
//        emit event_noteon(n);
//#endif
//    }
//    else if ( event->type() == NoteOffEventType ) {
//        NoteOffEvent *ev = static_cast<NoteOffEvent*>(event);
//        int n = ev->getNote();
//        ui.pianokeybd->showNoteOff(n);
//#ifdef ENABLE_DBUS
//        emit event_noteoff(n);
//#endif
//    }
//    else if ( event->type() == PolyKeyPressEventType ) {
//#ifdef ENABLE_DBUS
//        PolyKeyPressEvent *ev = static_cast<PolyKeyPressEvent*>(event);
//        int n = ev->getNote();
//        int v = ev->getValue();
//        emit event_polykeypress(n, v);
//#endif
//    }
//    else if ( event->type() ==  ControlChangeEventType ) {
//        ControlChangeEvent *ev = static_cast<ControlChangeEvent*>(event);
//        int ctl = ev->getController();
//        int val = ev->getValue();
//        updateController(ctl, val);
//        updateExtraController(ctl, val);
//#ifdef ENABLE_DBUS
//        emit event_controlchange(ctl, val);
//#endif
//    }
//    else if ( event->type() ==  ProgramChangeEventType) {
//        ProgramChangeEvent *ev = static_cast<ProgramChangeEvent*>(event);
//        int val = ev->getValue();
//        updateProgramChange(val);
//#ifdef ENABLE_DBUS
//        emit event_programchange(val);
//#endif
//    }
//    else if ( event->type() ==  ChannelKeyPressEventType ) {
//#ifdef ENABLE_DBUS
//        ChannelKeyPressEvent *ev = static_cast<ChannelKeyPressEvent*>(event);
//        int val = ev->getValue();
//        emit event_chankeypress(val);
//#endif
//    }
//    else if ( event->type() ==  PitchWheelEventType ) {
//        PitchWheelEvent *ev = static_cast<PitchWheelEvent*>(event);
//        int val = ev->getValue();
//        m_bender->setValue(val);
//        m_bender->setToolTip(QString::number(val));
//#ifdef ENABLE_DBUS
//        emit event_pitchwheel(val);
//#endif
//    }
//    event->accept();
//}

//void VPiano::showEvent ( QShowEvent *event )
//{
//    if (m_initialized) {
//        QMainWindow::showEvent(event);
//        ui.pianokeybd->setFocus();
//        grabKb();
//    }
//}
//
//void VPiano::hideEvent( QHideEvent *event )
//{
//    releaseKb();
//    QMainWindow::hideEvent(event);
//}
//
//void VPiano::midiThru(std::vector<unsigned char> *message) const
//{
//    if (m_midiThru) {
//        try {
//            m_midiout->sendMessage( message );
//        } catch (RtError& err) {
//            qWarning() << QString::fromStdString(err.getMessage());
//        }
//    }
//}

void VPiano::sendMessageWrapper(std::vector<unsigned char> *message) const
{
    try {
        m_midiout->sendMessage( message );
    } catch (RtError& err) {
        printf("Something went south in SendMessageWrapper\n");
        //ui.statusBar->showMessage(QString::fromStdString(err.getMessage()));
    }
}

void VPiano::sendNoteOn(const int midiNote, const int velocity)
{
    std::vector<unsigned char> message;
    if ((midiNote & MASK_SAFETY) == midiNote) {
        unsigned char chan = static_cast<unsigned char>(m_channel);
        unsigned char vel = static_cast<unsigned char>(velocity);
        // Note On: 0x90 + channel, note, vel
        message.push_back(STATUS_NOTEON + (chan & MASK_CHANNEL));
        message.push_back(midiNote & MASK_SAFETY);
        message.push_back(vel & MASK_SAFETY);
        sendMessageWrapper( &message );
    }
}

//void VPiano::sendNoteOn(const int midiNote)
//{
//    std::vector<unsigned char> message;
//    if ((midiNote & MASK_SAFETY) == midiNote) {
//        unsigned char chan = static_cast<unsigned char>(m_channel);
//        unsigned char vel = static_cast<unsigned char>(m_velocity);
//        // Note On: 0x90 + channel, note, vel
//        message.push_back(STATUS_NOTEON + (chan & MASK_CHANNEL));
//        message.push_back(midiNote & MASK_SAFETY);
//        message.push_back(vel & MASK_SAFETY);
//        sendMessageWrapper( &message );
//    }
//}
//
//void VPiano::noteOn(const int midiNote)
//{
//    sendNoteOn(midiNote);
//#ifdef ENABLE_DBUS
//    emit event_noteon(midiNote);
//#endif
//}
//
void VPiano::sendNoteOff(const int midiNote)
{
    std::vector<unsigned char> message;
    if ((midiNote & MASK_SAFETY) == midiNote) {
        unsigned char chan = static_cast<unsigned char>(m_channel);
        unsigned char vel = static_cast<unsigned char>(m_velocity);
        // Note Off: 0x80 + channel, note, vel
        message.push_back(STATUS_NOTEOFF + (chan & MASK_CHANNEL));
        message.push_back(midiNote & MASK_SAFETY);
        message.push_back(vel & MASK_SAFETY);
        sendMessageWrapper( &message );
    }
}

//void VPiano::noteOff(const int midiNote)
//{
//    sendNoteOff(midiNote);
//#ifdef ENABLE_DBUS
//    emit event_noteoff(midiNote);
//#endif
//}

void VPiano::sendController(const int controller, const int value)
{
    std::vector<unsigned char> message;
    unsigned char chan = static_cast<unsigned char>(m_channel);
    unsigned char ctl  = static_cast<unsigned char>(controller);
    unsigned char val  = static_cast<unsigned char>(value);
    // Controller: 0xB0 + channel, ctl, val
    message.push_back(STATUS_CTLCHG + (chan & MASK_CHANNEL));
    message.push_back(ctl & MASK_SAFETY);
    message.push_back(val & MASK_SAFETY);
    sendMessageWrapper( &message );
}

//void VPiano::resetAllControllers()
//{
//    sendController(CTL_RESET_ALL_CTL, 0);
//    int index = m_comboControl->currentIndex();
//    int ctl = m_comboControl->itemData(index).toInt();
//    int val = m_ctlState[m_channel][ctl];
//    initControllers(m_channel);
//    m_comboControl->setCurrentIndex(index);
//    m_Control->setValue(val);
//    m_Control->setToolTip(QString::number(val));
//    // extra controllers
//    QList<QWidget *> allWidgets = ui.toolBarExtra->findChildren<QWidget *>();
//    foreach(QWidget *w, allWidgets) {
//        QVariant c = w->property(MIDICTLNUMBER);
//        if (c.isValid()) {
//            ctl = c.toInt();
//            if (m_ctlState[m_channel].contains(ctl)) {
//                val = m_ctlState[m_channel][ctl];
//                QVariant p = w->property("value");
//                if (p.isValid()) {
//                    w->setProperty("value", val);
//                    w->setToolTip(QString::number(val));
//                    continue;
//                }
//                p = w->property("checked");
//                if (p.isValid()) {
//                    QVariant on = w->property(MIDICTLONVALUE);
//                    w->setProperty("checked", (val >= on.toInt()));
//                }
//            }
//        }
//    }
//}
//
//void VPiano::allNotesOff()
//{
//    sendController(CTL_ALL_NOTES_OFF, 0);
//    ui.pianokeybd->allKeysOff();
//}

void VPiano::sendProgramChange(const int program)
{
    std::vector<unsigned char> message;
    unsigned char chan = static_cast<unsigned char>(m_channel);
    unsigned char pgm  = static_cast<unsigned char>(program);
    // Program: 0xC0 + channel, pgm
    message.push_back(STATUS_PROGRAM + (chan & MASK_CHANNEL));
    message.push_back(pgm & MASK_SAFETY);
    sendMessageWrapper( &message );
}

//void VPiano::sendBankChange(const int bank)
//{
//    int method = (m_ins != NULL) ? m_ins->bankSelMethod() : 0;
//    int lsb, msb;
//    switch (method) {
//    case 0:
//        lsb = CALC_LSB(bank);
//        msb = CALC_MSB(bank);
//        sendController(CTL_MSB, msb);
//        sendController(CTL_LSB, lsb);
//        break;
//    case 1:
//        sendController(CTL_MSB, bank);
//        break;
//    case 2:
//        sendController(CTL_LSB, bank);
//        break;
//    default: /* if method is 3 or above, do nothing */
//        break;
//    }
//    m_lastBank[m_channel] = bank;
//}
//
void VPiano::sendPolyKeyPress(const int note, const int value)
{
    std::vector<unsigned char> message;
    unsigned char chan = static_cast<unsigned char>(m_channel);
    unsigned char midi_note  = static_cast<unsigned char>(note);
    unsigned char val  = static_cast<unsigned char>(value);
    // Polyphonic After-touch: 0xA0 + channel, note, value
    message.push_back(STATUS_POLYAFT + (chan & MASK_CHANNEL));
    message.push_back(midi_note & MASK_SAFETY);
    message.push_back(val & MASK_SAFETY);
    sendMessageWrapper( &message );
}

void VPiano::sendChanKeyPress(const int value)
{
    std::vector<unsigned char> message;
    unsigned char chan = static_cast<unsigned char>(m_channel);
    unsigned char val  = static_cast<unsigned char>(value);
    // Channel After-touch: 0xD0 + channel, value
    message.push_back(STATUS_CHANAFT + (chan & MASK_CHANNEL));
    message.push_back(val & MASK_SAFETY);
    sendMessageWrapper( &message );
}

void VPiano::sendBender(const int value)
{
    std::vector<unsigned char> message;
    int v = value + BENDER_MID; // v >= 0, v <= 16384
    unsigned char chan = static_cast<unsigned char>(m_channel);
    unsigned char lsb  = static_cast<unsigned char>(CALC_LSB(v));
    unsigned char msb  = static_cast<unsigned char>(CALC_MSB(v));
    // Program: 0xE0 + channel, lsb, msb
    message.push_back(STATUS_BENDER + (chan & MASK_CHANNEL));
    message.push_back(lsb);
    message.push_back(msb);
    sendMessageWrapper( &message );
}
//
//void VPiano::slotPanic()
//{
//    allNotesOff();
//}
//
//void VPiano::slotResetAllControllers()
//{
//    resetAllControllers();
//}
//
//void VPiano::slotResetBender()
//{
//    m_bender->setValue(0);
//    sendBender(0);
//}
//
//void VPiano::sendSysex(const QByteArray& data)
//{
//    std::vector<unsigned char> message;
//    foreach(const char byte, data) {
//        message.push_back(byte);
//    }
//    sendMessageWrapper( &message );
//}
//
//void VPiano::slotControlClicked(const bool boolValue)
//{
//    QObject *s = sender();
//    QVariant p = s->property(MIDICTLNUMBER);
//    if (p.isValid()) {
//        int controller = p.toInt();
//        if (controller < 128) {
//            QVariant on = s->property(MIDICTLONVALUE);
//            QVariant off = s->property(MIDICTLOFFVALUE);
//            int value = boolValue ? on.toInt() : off.toInt();
//            sendController( controller, value );
//            updateController( controller, value );
//        } else {
//            QVariant data = s->property(SYSEXFILEDATA);
//            sendSysex(data.toByteArray());
//        }
//    }
//}
//
//void VPiano::slotVelocityValueChanged(int value)
//{
//    m_velocity = value;
//    setWidgetTip(m_Velocity, value);
//}
//
//void VPiano::slotExtraController(const int value)
//{
//    QWidget *w = static_cast<QWidget *>(sender());
//    QVariant p = w->property(MIDICTLNUMBER);
//    if (p.isValid()) {
//        int controller = p.toInt();
//        sendController( controller, value );
//        updateController( controller, value );
//        setWidgetTip(w, value);
//    }
//}
//
//void VPiano::slotControlSliderMoved(const int value)
//{
//    int index = m_comboControl->currentIndex();
//    int controller = m_comboControl->itemData(index).toInt();
//    sendController( controller, value );
//    updateExtraController( controller, value );
//    m_ctlState[m_channel][controller] = value;
//    setWidgetTip(m_Control, value);
//}
//
//void VPiano::slotBenderSliderMoved(const int pos)
//{
//    sendBender(pos);
//    setWidgetTip(m_bender, pos);
//}
//
//void VPiano::slotBenderSliderReleased()
//{
//    m_bender->setValue(0);
//    sendBender(0);
//    setWidgetTip(m_bender, 0);
//}
//
//void VPiano::slotAbout()
//{
//    releaseKb();
//    dlgAbout()->exec();
//    grabKb();
//}
//
//void VPiano::slotAboutQt()
//{
//    releaseKb();
//    QApplication::aboutQt();
//    grabKb();
//}
//
//void VPiano::refreshConnections()
//{
//    int i = 0, nInPorts = 0, nOutPorts = 0;
//    try {
//        dlgMidiSetup()->clearCombos();
//        // inputs
//        if (m_midiin == NULL) {
//            dlgMidiSetup()->inputNotAvailable();
//            dlgMidiSetup()->setInputEnabled(false);
//        } else {
//#if !defined(__LINUX_ALSASEQ__) && !defined(__MACOSX_CORE__)
//            dlgMidiSetup()->setInputEnabled(m_currentIn != -1);
//#endif
//            dlgMidiSetup()->addInputPortName(QString::null, -1);
//            nInPorts = m_midiin->getPortCount();
//            for ( i = 0; i < nInPorts; i++ ) {
//                QString name = QString::fromStdString(m_midiin->getPortName(i));
//                if (!name.startsWith(QSTR_VMPK))
//                    dlgMidiSetup()->addInputPortName(name, i);
//            }
//        }
//        // outputs
//        nOutPorts = m_midiout->getPortCount();
//        for ( i = 0; i < nOutPorts; i++ ) {
//            QString name = QString::fromStdString(m_midiout->getPortName(i));
//            if (!name.startsWith(QSTR_VMPK))
//                dlgMidiSetup()->addOutputPortName(name, i);
//        }
//    } catch (RtError& err) {
//        ui.statusBar->showMessage(QString::fromStdString(err.getMessage()));
//    }
//}
//
//void VPiano::slotConnections()
//{
//    refreshConnections();
//    dlgMidiSetup()->setCurrentInput(m_currentIn);
//    dlgMidiSetup()->setCurrentOutput(m_currentOut);
//    releaseKb();
//    if (dlgMidiSetup()->exec() == QDialog::Accepted) {
//        applyConnections();
//    }
//    grabKb();
//}
//
//void VPiano::applyConnections()
//{
//    int i, nInPorts = 0, nOutPorts = 0;
//    try {
//        nOutPorts = m_midiout->getPortCount();
//        i = dlgMidiSetup()->selectedOutput();
//        if ((i >= 0) && (i < nOutPorts) && (i != m_currentOut)) {
//            m_midiout->closePort();
//            m_midiout->openPort(i);
//        }
//        m_currentOut = i;
//        if (m_midiin != NULL) {
//            nInPorts = m_midiin->getPortCount();
//            i = dlgMidiSetup()->selectedInput();
//            if (m_inputActive && (i != m_currentIn)) {
//                m_midiin->cancelCallback();
//                m_inputActive = false;
//                if (m_currentIn > -1)
//                    m_midiin->closePort();
//            }
//            if ((i >= 0) && (i < nInPorts) && (i != m_currentIn) &&
//                dlgMidiSetup()->inputIsEnabled()) {
//                m_midiin->openPort(i);
//                m_midiin->setCallback( &midiCallback, this );
//                m_inputActive = true;
//            }
//            m_currentIn = i;
//            m_midiThru = dlgMidiSetup()->thruIsEnabled();
//        }
//    } catch (RtError& err) {
//        ui.statusBar->showMessage(QString::fromStdString(err.getMessage()));
//    }
//}
//
//void VPiano::initControllers(int channel)
//{
//    if (m_ins != NULL) {
//        InstrumentData controls = m_ins->control();
//        InstrumentData::ConstIterator it, end;
//        it = controls.constBegin();
//        end = controls.constEnd();
//        for( ; it != end; ++it ) {
//            int ctl = it.key();
//            switch (ctl) {
//            case CTL_VOLUME:
//                m_ctlState[channel][CTL_VOLUME] = 100;
//                break;
//            case CTL_PAN:
//                m_ctlState[channel][CTL_PAN] = 64;
//                break;
//            case CTL_EXPRESSION:
//                m_ctlState[channel][CTL_EXPRESSION] = 127;
//                break;
//            default:
//                m_ctlState[channel][ctl] = 0;
//            }
//        }
//    }
//}
//
//void VPiano::populateControllers()
//{
//    m_comboControl->blockSignals(true);
//    m_comboControl->clear();
//    if (m_ins != NULL) {
//        InstrumentData controls = m_ins->control();
//        InstrumentData::ConstIterator it, end = controls.constEnd();
//        for( it = controls.constBegin(); it != end; ++it )
//            m_comboControl->addItem(it.value(), it.key());
//    }
//    m_comboControl->blockSignals(false);
//}
//
//void VPiano::applyPreferences()
//{
//    ui.pianokeybd->allKeysOff();
//
//    if (ui.pianokeybd->baseOctave() != m_baseOctave) {
//        ui.pianokeybd->setBaseOctave(m_baseOctave);
//    }
//    if (ui.pianokeybd->numOctaves() != dlgPreferences()->getNumOctaves()) {
//        ui.pianokeybd->setNumOctaves(dlgPreferences()->getNumOctaves());
//    }
//    ui.pianokeybd->setKeyPressedColor(dlgPreferences()->getKeyPressedColor());
//    ui.pianokeybd->setRawKeyboardMode(dlgPreferences()->getRawKeyboard());
//
//    KeyboardMap* map = dlgPreferences()->getKeyboardMap();
//    if (!map->getFileName().isEmpty() && map->getFileName() != QSTR_DEFAULT )
//        ui.pianokeybd->setKeyboardMap(map);
//    else
//        ui.pianokeybd->resetKeyboardMap();
//
//    map = dlgPreferences()->getRawKeyboardMap();
//    if (!map->getFileName().isEmpty() && map->getFileName() != QSTR_DEFAULT )
//        ui.pianokeybd->setRawKeyboardMap(map);
//    else
//        ui.pianokeybd->resetRawKeyboardMap();
//
//    populateInstruments();
//    populateControllers();
//
//    QPoint wpos = pos();
//    Qt::WindowFlags flags = windowFlags();
//    if (dlgPreferences()->getAlwaysOnTop())
//        flags |= Qt::WindowStaysOnTopHint;
//    else
//        flags &= ~Qt::WindowStaysOnTopHint;
//    setWindowFlags( flags );
//    move(wpos);
//
//    slotShowNoteNames();
//    updateStyles();
//    show();
//}
//
//void VPiano::populateInstruments()
//{
//    m_ins = NULL;
//    m_comboBank->clear();
//    m_comboProg->clear();
//    if (!dlgPreferences()->getInstrumentsFileName().isEmpty() &&
//         dlgPreferences()->getInstrumentsFileName() != QSTR_DEFAULT) {
//        if (m_channel == dlgPreferences()->getDrumsChannel())
//            m_ins = dlgPreferences()->getDrumsInstrument();
//        else
//            m_ins = dlgPreferences()->getInstrument();
//        if (m_ins != NULL) {
//            //qDebug() << "Instrument Name:" << m_ins->instrumentName();
//            //qDebug() << "Bank Selection method: " << m_ins->bankSelMethod();
//            InstrumentPatches patches = m_ins->patches();
//            InstrumentPatches::ConstIterator j;
//            for( j = patches.constBegin(); j != patches.constEnd(); ++j ) {
//                //if (j.key() < 0) continue;
//                InstrumentData patch = j.value();
//                m_comboBank->addItem(patch.name(), j.key());
//                //qDebug() << "---- Bank[" << j.key() << "]=" << patch.name();
//            }
//            updateBankChange(m_lastBank[m_channel]);
//        }
//    }
//}
//
//void VPiano::applyInitialSettings()
//{
//    int idx, ctl;
//    for ( int ch=0; ch<MIDICHANNELS; ++ch) {
//        initControllers(ch);
//        QMap<int,int>::Iterator i, j, end;
//        i = m_ctlSettings[ch].begin();
//        end = m_ctlSettings[ch].end();
//        for (; i != end; ++i) {
//            j = m_ctlState[ch].find(i.key());
//            if (j != m_ctlState[ch].end())
//                m_ctlState[ch][i.key()] = i.value();
//        }
//    }
//    ctl = m_lastCtl[m_channel];
//    idx = m_comboControl->findData(ctl);
//    if (idx != -1)
//        m_comboControl->setCurrentIndex(idx);
//    //slotControlSliderMoved(m_ctlState[m_channel][ctl]);
//    updateBankChange(m_lastBank[m_channel]);
//    idx = m_comboProg->findData(m_lastProg[m_channel]);
//    m_comboProg->setCurrentIndex(idx);
//    //slotComboProgActivated(idx);
//}
//
//void VPiano::slotPreferences()
//{
//    releaseKb();
//    if (dlgPreferences()->exec() == QDialog::Accepted) {
//        applyPreferences();
//    }
//    grabKb();
//}
//
//QString VPiano::dataDirectory()
//{
//#ifdef Q_OS_WIN32
//    return QApplication::applicationDirPath() + "/";
//#endif
//#ifdef Q_OS_LINUX
//    return QApplication::applicationDirPath() + "/../share/vmpk/";
//#endif
//#ifdef Q_OS_DARWIN
//    return QApplication::applicationDirPath() + "/../Resources/";
//#endif
//    return QString();
//}
//
//void VPiano::slotEditKeyboardMap()
//{
//    KeyboardMap* map;
//    releaseKb();
//    if (dlgPreferences()->getRawKeyboard())
//        map = ui.pianokeybd->getRawKeyboardMap();
//    else
//        map = ui.pianokeybd->getKeyboardMap();
//    dlgKeyMap()->displayMap(map);
//    if (dlgKeyMap()->exec() == QDialog::Accepted) {
//        dlgKeyMap()->getMap(map);
//        if (dlgPreferences()->getRawKeyboard())
//            ui.pianokeybd->setRawKeyboardMap(map);
//        else
//            ui.pianokeybd->setKeyboardMap(map);
//    }
//    grabKb();
//}
//
//void VPiano::populatePrograms(int bank)
//{
//    if (bank < 0)
//        return;
//    m_comboProg->clear();
//    if (m_ins != NULL) {
//        InstrumentData patch = m_ins->patch(bank);
//        InstrumentData::ConstIterator k;
//        for( k = patch.constBegin(); k != patch.constEnd(); ++k )
//            m_comboProg->addItem(k.value(), k.key());
//            //qDebug() << "patch[" << k.key() << "]=" << k.value();
//    }
//}
//
//void VPiano::slotComboBankActivated(const int index)
//{
//    int idx = index;
//    if (idx < 0)
//        m_comboBank->setCurrentIndex(idx = 0);
//    int bank = m_comboBank->itemData(idx).toInt();
//    populatePrograms(bank);
//    slotComboProgActivated();
//}
//
//void VPiano::slotComboProgActivated(const int index)
//{
//    int idx = index;
//    if (idx < 0)
//        m_comboProg->setCurrentIndex(idx = 0);
//    int bankIdx = m_comboBank->currentIndex();
//    int bank = m_comboBank->itemData(bankIdx).toInt();
//    if (bank >= 0) {
//        sendBankChange(bank);
//        m_lastBank[m_channel] = bank;
//    }
//    int pgm = m_comboProg->itemData(idx).toInt();
//    if (pgm >= 0) {
//        sendProgramChange(pgm);
//        m_lastProg[m_channel] = pgm;
//    }
//    updateNoteNames(m_channel == dlgPreferences()->getDrumsChannel());
//}
//
//void VPiano::slotBaseOctaveValueChanged(const int octave)
//{
//    if (octave != m_baseOctave) {
//        ui.pianokeybd->allKeysOff();
//        ui.pianokeybd->setBaseOctave(octave);
//        m_baseOctave = octave;
//    }
//}
//
//void VPiano::slotTransposeValueChanged(const int transpose)
//{
//    if (transpose != m_transpose) {
//        ui.pianokeybd->setTranspose(transpose);
//        m_transpose = transpose;
//        }
//}
//
//void VPiano::updateNoteNames(bool drums)
//{
//    if (drums && (m_ins != NULL)) {
//        int b = m_lastBank[m_channel];
//        int p = m_lastProg[m_channel];
//        const InstrumentData& notes = m_ins->notes(b, p);
//        QStringList noteNames;
//        for(int n=0; n<128; ++n) {
//            if (notes.contains(n))
//                noteNames << notes[n];
//            else
//                noteNames << QString();
//        }
//        ui.pianokeybd->useCustomNoteNames(noteNames);
//    } else
//        ui.pianokeybd->useStandardNoteNames();
//}
//
//void VPiano::slotChannelValueChanged(const int channel)
//{
//    int idx;
//    int c = channel - 1;
//    if (c != m_channel) {
//        int drms = dlgPreferences()->getDrumsChannel();
//        bool updDrums = ((c == drms) || (m_channel == drms));
//        m_channel = c;
//        if (updDrums) {
//            populateInstruments();
//            populateControllers();
//        }
//        idx = m_comboControl->findData(m_lastCtl[m_channel]);
//        if (idx != -1) {
//            int ctl = m_lastCtl[m_channel];
//            m_comboControl->setCurrentIndex(idx);
//            updateController(ctl, m_ctlState[m_channel][ctl]);
//            updateExtraController(ctl, m_ctlState[m_channel][ctl]);
//        }
//        updateBankChange(m_lastBank[m_channel]);
//        updateProgramChange(m_lastProg[m_channel]);
//    }
//}
//
//void VPiano::updateController(int ctl, int val)
//{
//    int index = m_comboControl->currentIndex();
//    int controller = m_comboControl->itemData(index).toInt();
//    if (controller == ctl) {
//        m_Control->setValue(val);
//        m_Control->setToolTip(QString::number(val));
//    }
//    m_ctlState[m_channel][ctl] = val;
//    if ((ctl == CTL_MSB || ctl == CTL_LSB ) && m_ins != NULL) {
//        if (m_ins->bankSelMethod() == 0)
//            m_lastBank[m_channel] = m_ctlState[m_channel][CTL_MSB] << 7 |
//                                    m_ctlState[m_channel][CTL_LSB];
//        else
//            m_lastBank[m_channel] = val;
//
//        updateBankChange(m_lastBank[m_channel]);
//    }
//}
//
//void VPiano::updateExtraController(int ctl, int val)
//{
//    QList<QWidget *> allWidgets = ui.toolBarExtra->findChildren<QWidget *>();
//    foreach(QWidget *w, allWidgets) {
//        QVariant p = w->property(MIDICTLNUMBER);
//        if (p.isValid() && p.toInt() == ctl) {
//            QVariant v = w->property("value");
//            if (v.isValid() && v.toInt() != val) {
//                w->setProperty("value", val);
//                w->setToolTip(QString::number(val));
//                continue;
//            }
//            v = w->property("checked");
//            if (v.isValid()) {
//                QVariant on = w->property(MIDICTLONVALUE);
//                bool checked = (val >= on.toInt());
//                w->setProperty("checked", checked);
//            }
//        }
//    }
//}
//
//void VPiano::updateBankChange(int bank)
//{
//    int idx;
//    if (bank < 0) {
//        m_comboBank->setCurrentIndex(idx = 0);
//        bank = m_comboBank->itemData(idx).toInt();
//        if (bank < 0)
//            bank = 0;
//    } else {
//        idx = m_comboBank->findData(bank);
//        if (idx != -1) {
//            m_comboBank->setCurrentIndex(idx);
//            m_lastBank[m_channel] = bank;
//        }
//    }
//    populatePrograms(bank);
//    updateProgramChange();
//}
//
//void VPiano::updateProgramChange(int program)
//{
//    int idx;
//    if (program < 0) {
//        m_comboProg->setCurrentIndex(idx = 0);
//        program = m_comboProg->itemData(idx).toInt();
//    } else {
//        idx = m_comboProg->findData(program);
//        if (idx != -1) {
//            m_comboProg->setCurrentIndex(idx);
//            m_lastProg[m_channel] = program;
//        }
//    }
//    updateNoteNames(m_channel == dlgPreferences()->getDrumsChannel());
//}
//
//void VPiano::slotComboControlCurrentIndexChanged(const int index)
//{
//    int ctl = m_comboControl->itemData(index).toInt();
//    int val = m_ctlState[m_channel][ctl];
//    m_Control->setValue(val);
//    m_Control->setToolTip(QString::number(val));
//    m_lastCtl[m_channel] = ctl;
//    //slotControlSliderMoved(val);
//}
//
//void VPiano::grabKb()
//{
//    if (dlgPreferences()->getGrabKeyboard()) {
//        ui.pianokeybd->grabKeyboard();
//    }
//    ui.pianokeybd->setRawKeyboardMode(dlgPreferences()->getRawKeyboard());
//}
//
//void VPiano::releaseKb()
//{
//    if (dlgPreferences()->getGrabKeyboard()) {
//        ui.pianokeybd->releaseKeyboard();
//    }
//    ui.pianokeybd->setRawKeyboardMode(false);
//}
//
//void VPiano::slotHelpContents()
//{
//    QStringList hlps;
//    QLocale loc = QLocale::system();
//    QStringList lc = loc.name().split("_");
//    hlps += QString("help_%1.html").arg(loc.name());
//    if (lc.count() > 1)
//        hlps += QString("help_%1.html").arg(lc[0]);
//    hlps += "help.html";
//    foreach(const QString& hlp_name, hlps) {
//        QString fullName = VPiano::dataDirectory() + hlp_name;
//        if (QFile::exists(fullName)) {
//            QUrl url = QUrl::fromLocalFile(fullName);
//            QDesktopServices::openUrl(url);
//            return;
//        }
//    }
//    QMessageBox::critical(this, tr("Error"), tr("No help file found"));
//}
//
//void VPiano::slotOpenWebSite()
//{
//    QUrl url(QSTR_VMPKURL);
//    QDesktopServices::openUrl(url);
//}
//
//void VPiano::updateStyles()
//{
//    QList<Knob *> allKnobs = findChildren<Knob *> ();
//    foreach(Knob* knob, allKnobs) {
//        knob->setStyle(dlgPreferences()->getStyledWidgets() ? m_dialStyle : NULL);
//    }
//    QList<QCheckBox *> allChkbox = ui.toolBarExtra->findChildren<QCheckBox *> ();
//    foreach(QCheckBox* chkbox, allChkbox) {
//        chkbox->setStyle(dlgPreferences()->getStyledWidgets() ? m_dialStyle : NULL);
//    }
//}
//
//void VPiano::slotImportSF()
//{
//    releaseKb();
//    if ((dlgRiffImport()->exec() == QDialog::Accepted) &&
//        !dlgRiffImport()->getOutput().isEmpty()) {
//        dlgRiffImport()->save();
//        dlgPreferences()->setInstrumentsFileName(dlgRiffImport()->getOutput());
//        dlgPreferences()->setInstrumentName(dlgRiffImport()->getName());
//        applyPreferences();
//    }
//    grabKb();
//}
//
//void VPiano::slotEditExtraControls()
//{
//    dlgExtra()->setControls(m_extraControls);
//    releaseKb();
//    if (dlgExtra()->exec() == QDialog::Accepted) {
//        m_extraControls = dlgExtra()->getControls();
//        clearExtraControllers();
//        initExtraControllers();
//    }
//    grabKb();
//}
//
//About* VPiano::dlgAbout()
//{
//    if (m_dlgAbout == NULL) {
//        m_dlgAbout = new About(this);
//    }
//    return m_dlgAbout;
//}
//
//Preferences* VPiano::dlgPreferences()
//{
//    if (m_dlgPreferences == NULL) {
//        m_dlgPreferences = new Preferences(this);
//    }
//    return m_dlgPreferences;
//}
//
//MidiSetup* VPiano::dlgMidiSetup()
//{
//    if (m_dlgMidiSetup == NULL) {
//        m_dlgMidiSetup = new MidiSetup(this);
//    }
//    return m_dlgMidiSetup;
//}
//
//KMapDialog* VPiano::dlgKeyMap()
//{
//    if (m_dlgKeyMap == NULL) {
//        m_dlgKeyMap = new KMapDialog(this);
//    }
//    return m_dlgKeyMap;
//}
//
//DialogExtraControls* VPiano::dlgExtra()
//{
//    if (m_dlgExtra == NULL) {
//        m_dlgExtra = new DialogExtraControls(this);
//    }
//    return m_dlgExtra;
//}
//
//RiffImportDlg* VPiano::dlgRiffImport()
//{
//    if (m_dlgRiffImport == NULL) {
//        m_dlgRiffImport = new RiffImportDlg(this);
//    }
//    return m_dlgRiffImport;
//}
//
//void VPiano::setWidgetTip(QWidget* w, int val)
//{
//    QString tip = QString::number(val);
//    w->setToolTip(tip);
//    QToolTip::showText(QCursor::pos(), tip, this);
//}
//
//void VPiano::slotShowNoteNames()
//{
//    ui.pianokeybd->setShowLabels(ui.actionNoteNames->isChecked());
//}

//void VPiano::slotEditPrograms()
//{ }

//#if ENABLE_DBUS
//
//void VPiano::quit()
//{
//    close();
//}
//
//void VPiano::panic()
//{
//    allNotesOff();
//}
//
//void VPiano::reset_controllers()
//{
//    resetAllControllers();
//}
//
//void VPiano::channel(int value)
//{
//    if (value >= 0 && value < MIDICHANNELS)
//        m_sboxChannel->setValue(value + 1);
//}
//
//void VPiano::octave(int value)
//{
//    m_sboxOctave->setValue(value);
//}
//
//void VPiano::transpose(int value)
//{
//    m_sboxTranspose->setValue(value);
//}
//
//void VPiano::velocity(int value)
//{
//    m_Velocity->setValue(value);
//}
//
//void VPiano::connect_in(const QString &value)
//{
//    if( m_midiin != 0) {
//        dlgMidiSetup()->setInputEnabled(true);
//        dlgMidiSetup()->setCurrentInput(value);
//        applyConnections();
//    }
//}
//
//void VPiano::connect_out(const QString &value)
//{
//    if( m_midiout != 0) {
//        dlgMidiSetup()->setCurrentOutput(value);
//        applyConnections();
//    }
//}
//
//void VPiano::connect_thru(bool value)
//{
//    if( m_midiin != 0 && m_midiout != 0) {
//        dlgMidiSetup()->setThruEnabled(value);
//        applyConnections();
//    }
//}
//
//void VPiano::noteoff(int note)
//{
//    sendNoteOff(note);
//    NoteOffEvent *ev = new NoteOffEvent(note);
//    QApplication::postEvent(this, ev);
//}
//
//void VPiano::noteon(int note)
//{
//    sendNoteOn(note);
//    NoteOnEvent *ev = new NoteOnEvent(note);
//    QApplication::postEvent(this, ev);
//}
//
//void VPiano::polykeypress(int note, int value)
//{
//    sendPolyKeyPress(note, value);
//    PolyKeyPressEvent *ev = new PolyKeyPressEvent(note, value);
//    QApplication::postEvent(this, ev);
//}
//
//void VPiano::controlchange(int control, int value)
//{
//    sendController(control, value);
//    ControlChangeEvent *ev = new ControlChangeEvent(control, value);
//    QApplication::postEvent(this, ev);
//}
//
//void VPiano::programchange(int value)
//{
//    sendProgramChange(value);
//    ProgramChangeEvent *ev = new ProgramChangeEvent(value);
//    QApplication::postEvent(this, ev);
//}
//
//void VPiano::programnamechange(const QString &value)
//{
//    int idx = m_comboProg->findText(value, Qt::MatchFixedString);
//    if (idx != -1) {
//        int prg = m_comboProg->itemData(idx).toInt();
//        programchange(prg);
//    }
//}
//
//void VPiano::chankeypress(int value)
//{
//    sendChanKeyPress(value);
//    ChannelKeyPressEvent *ev = new ChannelKeyPressEvent(value);
//    QApplication::postEvent(this, ev);
//}
//
//void VPiano::pitchwheel(int value)
//{
//    sendBender(value);
//    PitchWheelEvent *ev = new PitchWheelEvent(value);
//    QApplication::postEvent(this, ev);
//}

//#endif /* ENABLE_DBUS */
