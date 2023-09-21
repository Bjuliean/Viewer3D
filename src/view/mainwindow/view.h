#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QColorDialog>
#include <QTimer>
#include <QSettings>

#include "libs/QtGifImage/src/gifimage/qgifimage.h"
#include "../controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class view; }
QT_END_NAMESPACE

namespace s21 {

class IObserver {
public:
    virtual void Update() = 0;

}; // IObserver

class IObservable {
public:
    virtual void AddObserver(IObserver *o) = 0;
    virtual void RemoveObserver(IObserver *o) = 0;
    virtual void Notify() = 0;
    virtual ~IObservable() {}

}; // IObservable

/*!
    \brief A class that handles events associated with some buttons.

    Some buttons require instant frame refresh. 
    To track changes in the user interface, as well as for comfortable code extensibility, 
    it was decided to use the “Observer” pattern.
*/
class ButtonsRegulator : public QObject, public IObservable {

    Q_OBJECT

public:
    ButtonsRegulator(Ui::view *ui);
    ~ButtonsRegulator() = default;

    void AddObserver(IObserver *o) override {
        observers_.push_back(o);
    }

    void RemoveObserver(IObserver *o) override {
        observers_.erase(remove(observers_.begin(), observers_.end(), o), observers_.end());
    }

    void Notify() override {
        for(auto it : observers_) it->Update();
    }

    /*! A method that allows you to set the text color of a button. */
    static void SetButtonColor(QPushButton *button, QColor color);
    /*! A method that allows you to get the text color of a button. */
    static QColor GetButtonColor(QPushButton *button);

private slots:
    /*! Loading File */
    void LoadFile();
    /*! Loading Texture */
    void LoadTexture();
    /*! A slot that contains interface elements that require immediate frame updating. */
    void InitiatorButtons();
    /*! Changing widget background color. */
    void ChangeBackgroundColor();
    /*! Changing vertices color. */
    void ChangeVerticesColor();
    /*! Changing lines color. */
    void ChangeLinesColor();
    /*! Allows you to save a screenshot in bmp or jpeg format. */
    void SaveScreenshot();
    /*! Allows you to save a gif. */
    void SaveGif();
    /*! A slot responsible for actions that occur over the course of the timer. */
    void TimerFlow();

private:
    std::vector<IObserver*> observers_;
    Ui::view *uiwindow_;
    QTimer *timer_;
    QGifImage *gif_;
    QImage *gif_image_;
    size_t gif_time_;

}; // ButtonsRegulator

/*! \brief Base class of the view. */
class view : public QMainWindow, public IObserver
{
    Q_OBJECT

public:
    view(QWidget *parent = nullptr);
    ~view();

    void Update() override;

private slots:
    /*! Allows you to save the current transformations. */
    void on_pushButton_savecfg_clicked();
    /*! Allows you to restore the current transformations by index. */
    void on_pushButton_undocfg_clicked();
    /*! Allows you to remove the current transformations by index. */
    void on_pushButton_deletecfg_clicked();
    /*! Allows you to load some settings from the previous session. */
    void on_pushButton_loadsettings_clicked();
    /*! Allows you to reset all transformations. */
    void on_pushButton_reset_clicked();

private:
    Ui::view *ui;
    s21::Controller controller_;
    IObservable *buttons_;
    Memory *cfgs_;
    QSettings settings_;

    /*! Support method, saves some settings. */
    void SaveSettings();
    /*! Support method, restores settings from the previous session. */
    void LoadSettings();

}; // view

}; // namespace s21

#endif // VIEW_H
