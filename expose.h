#ifndef EXPOSE_H
#define EXPOSE_H

#include <QJsonObject>

class ExposeObject;
typedef QSharedPointer <ExposeObject> Expose;

class ExposeObject
{

public:

    ExposeObject(const QString &name, const QString &component) :
        m_name(name), m_component(component), m_parent(nullptr), m_multiple(false), m_homeassistant(true) {}

    ExposeObject(const QString &name) :
        m_name(name), m_parent(nullptr), m_multiple(false), m_homeassistant(false) {}

    virtual ~ExposeObject(void) {}
    virtual QJsonObject reqest(void) { return QJsonObject(); };

    inline QString name(void) { return m_name; }
    inline QString component(void) { return m_component; }

    inline void setStateTopic(const QString &value) { m_stateTopic = value; }
    inline void setCommandTopic(const QString &value) { m_commandTopic = value; }
    inline void setParent(QObject *value) { m_parent = value; }

    inline bool multiple(void) { return m_multiple; }
    inline void setMultiple(bool value) { m_multiple = value; }

    inline bool homeassistant(void) { return m_homeassistant; }
    static void registerMetaTypes(void);

    QVariant endpointOption(const QString &name = QString());

protected:

    QString m_name, m_component, m_stateTopic, m_commandTopic;

    QObject *m_parent;
    bool m_multiple, m_homeassistant;

};

class BinaryObject : public ExposeObject
{

public:

    BinaryObject(const QString &name = "alarm") : ExposeObject(name, "binary_sensor") {}
    QJsonObject reqest(void) override;

};

class SensorObject : public ExposeObject
{

public:

    SensorObject(const QString &name, const QString &unit = QString(), quint8 round = 0) : ExposeObject(name, "sensor"), m_unit(unit), m_round(round) {}
    QJsonObject reqest(void) override;

private:

    QString m_unit;
    quint8 m_round;

};

class NumberObject : public ExposeObject
{

public:

    NumberObject(const QString &name, const QString &icon = QString()) : ExposeObject(name, "number"), m_icon(icon) {}
    QJsonObject reqest(void) override;

private:

    QString m_icon;

};

class ButtonObject : public ExposeObject
{

public:

    ButtonObject(const QString &name, const QString &payload) : ExposeObject(name, "button"), m_payload(payload) {}
    QJsonObject reqest(void) override;

private:

    QString m_payload;

};

class LightObject : public ExposeObject
{

public:

    LightObject(void) : ExposeObject("light", "light") {}
    QJsonObject reqest(void) override;

};

class SwitchObject : public ExposeObject
{

public:

    SwitchObject(void) : ExposeObject("switch", "switch") {}
    QJsonObject reqest(void) override;

};

class CoverObject : public ExposeObject
{

public:

    CoverObject(void) : ExposeObject("cover", "cover") {}
    QJsonObject reqest(void) override;

};

class ThermostatObject : public ExposeObject
{

public:

    ThermostatObject(void) : ExposeObject("thermostat", "climate") {}
    QJsonObject reqest(void) override;

};

namespace Binary
{
    class Contact : public BinaryObject
    {

    public:

        Contact(void) : BinaryObject("contact") {}

    };

    class Gas : public BinaryObject
    {

    public:

        Gas(void) : BinaryObject("gas") {}

    };

    class Occupancy : public BinaryObject
    {

    public:

        Occupancy(void) : BinaryObject("occupancy") {}

    };

    class Smoke : public BinaryObject
    {

    public:

        Smoke(void) : BinaryObject("smoke") {}

    };

    class WaterLeak : public BinaryObject
    {

    public:

        WaterLeak(void) : BinaryObject("waterLeak") {}

    };

    class Vibration : public BinaryObject
    {

    public:

        Vibration(void) : BinaryObject("vibration") {}

    };
}

namespace Sensor
{
    class Battery : public SensorObject
    {

    public:

        Battery(void) : SensorObject("battery", "%", 1) {}

    };

    class Temperature : public SensorObject
    {

    public:

        Temperature(void) : SensorObject("temperature", "°C", 1) {}

    };

    class Pressure : public SensorObject
    {

    public:

        Pressure(void) : SensorObject("pressure", "kPa", 1) {}

    };

    class Humidity : public SensorObject
    {

    public:

        Humidity(void) : SensorObject("humidity", "%", 1) {}

    };

    class Moisture : public SensorObject
    {

    public:

        Moisture(void) : SensorObject("moisture", "%", 1) {}

    };

    class Illuminance : public SensorObject
    {

    public:

        Illuminance(void) : SensorObject("illuminance", "lux") {}

    };

    class CO2 : public SensorObject
    {

    public:

        CO2(void) : SensorObject("co2", "ppm") {}

    };

    class VOC : public SensorObject
    {

    public:

        VOC(void) : SensorObject("voc", "ppb") {}

    };

    class Energy : public SensorObject
    {

    public:

        Energy(void) : SensorObject("energy", "kW·h", 2) {}

    };

    class Voltage : public SensorObject
    {

    public:

        Voltage(void) : SensorObject("voltage", "V", 1) {}

    };

    class Current : public SensorObject
    {

    public:

        Current(void) : SensorObject("current", "A", 3) {}

    };

    class Power : public SensorObject
    {

    public:

        Power(void) : SensorObject("power", "W", 2) {}

    };

    class Count : public SensorObject
    {

    public:

        Count(void) : SensorObject("count") {}

    };

    class Action : public SensorObject
    {

    public:

        Action(void) : SensorObject("action") {}

    };

    class Event : public SensorObject
    {

    public:

        Event(void) : SensorObject("event") {}

    };

    class Scene : public SensorObject
    {

    public:

        Scene(void) : SensorObject("scene") {}

    };
}

namespace Number
{
    class Pattern : public NumberObject
    {

    public:

        Pattern(void) : NumberObject("pattern", "mdi:swap-horizontal-bold") {}

    };

    class Timer : public NumberObject
    {

    public:

        Timer(void) : NumberObject("timer", "mdi:clock") {}

    };

    class Threshold : public NumberObject
    {

    public:

        Threshold(void) : NumberObject("threshold", "mdi:percent") {}

    };
}

namespace Button
{
    class ResetCount : public ButtonObject
    {

    public:

        ResetCount(void) : ButtonObject("resetCount", "{\"count\":0}") {}

    };
}

#endif