#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QImage>
#include <QDebug>
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    FSupdateButtonState();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateDatabaseInfo()
{
    ui->FScomboBox->clear();
    for(unsigned int i=1; i<=database.getNoFeatures(); ++i)
        ui->FScomboBox->addItem(QString::number(i));

    ui->FStextBrowserDatabaseInfo->setText("noClass: " +  QString::number(database.getNoClass()));
    ui->FStextBrowserDatabaseInfo->append("noObjects: "  +  QString::number(database.getNoObjects()));
    ui->FStextBrowserDatabaseInfo->append("noFeatures: "  +  QString::number(database.getNoFeatures()));

}

void MainWindow::FSupdateButtonState(void)
{
    if(database.getNoObjects()==0)
    {
        FSsetButtonState(false);
    }
    else
        FSsetButtonState(true);

}


void MainWindow::FSsetButtonState(bool state)
{
   ui->FScomboBox->setEnabled(state);
   ui->FSpushButtonCompute->setEnabled(state);
   ui->FSpushButtonSaveFile->setEnabled(state);
   ui->FSradioButtonFisher->setEnabled(state);
   ui->FSradioButtonSFS->setEnabled(state);
}

void MainWindow::on_FSpushButtonOpenFile_clicked()
{
    openFile();
    FSupdateButtonState();
    updateDatabaseInfo();
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open TextFile"), "", tr("Texts Files (*.txt)"));

    if (!database.load(fileName.toStdString()))
        QMessageBox::warning(this, "Warning", "File corrupted !!!");
    else
        QMessageBox::information(this, fileName, "File loaded !!!");
}

void MainWindow::on_FSpushButtonCompute_clicked()
{
    int dimension = ui->FScomboBox->currentText().toInt();


    if( ui->FSradioButtonFisher ->isChecked())
    {
    if (dimension == 1 && database.getNoClass() == 2)
        {
            float FLD = 0, tmp;
            int max_ind = -1;

            //std::map<std::string, int> classNames = database.getClassNames();
            for (uint i = 0; i < database.getNoFeatures(); ++i)
            {
                std::map<std::string, float> classAverages;
                std::map<std::string, float> classStds;

                for (auto const &ob : database.getObjects())
                {
                    classAverages[ob.getClassName()] += ob.getFeatures()[i];
                    classStds[ob.getClassName()] += ob.getFeatures()[i] * ob.getFeatures()[i];
                }

                std::for_each(database.getClassCounters().begin(), database.getClassCounters().end(), [&](const std::pair<std::string, int> &it)
                {
                    classAverages[it.first] /= it.second;
                    classStds[it.first] = std::sqrt(classStds[it.first] / it.second - classAverages[it.first] * classAverages[it.first]);
                }
                );

                tmp = std::abs(classAverages[ database.getClassNames()[0] ] - classAverages[database.getClassNames()[1]]) / (classStds[database.getClassNames()[0]] + classStds[database.getClassNames()[1]]);

                if (tmp > FLD)
                {
                    FLD = tmp;
                    max_ind = i;
                }

              }

            ui->FStextBrowserDatabaseInfo->append("max_ind: "  +  QString::number(max_ind) + " " + QString::number(FLD));
          }
     }
}



void MainWindow::on_FSpushButtonSaveFile_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
    tr("Open TextFile"), "D:\\Users\\Krzysiu\\Documents\\Visual Studio 2015\\Projects\\SMPD\\SMPD\\Debug\\", tr("Texts Files (*.txt)"));

        QMessageBox::information(this, "My File", fileName);
        database.save(fileName.toStdString());
}

void MainWindow::on_PpushButtonSelectFolder_clicked()
{
}

void MainWindow::on_CpushButtonOpenFile_clicked()
{
    openFile();
    bool anyObjectsFoundInFile = database.getObjects().size() > 0;
    ui->CpushButtonTrain->setEnabled(anyObjectsFoundInFile);

    if(!anyObjectsFoundInFile)
    {
            QMessageBox::information(this, "File loaded", "But it's empty...");
    }
}

void MainWindow::on_CpushButtonSaveFile_clicked()
{

}

void MainWindow::on_CpushButtonTrain_clicked()
{
     int percentageTrainValues = ui->CplainTextEditTrainingPart->toPlainText().toInt();
     bool canExecute = false;
     if (percentageTrainValues >= 100 || percentageTrainValues <= 0)
     {
         QMessageBox::warning(this, "Warning", "Percentage value should be in range 1-99");
     }
     else
     {
         objectsCount = database.getNoObjects();
         int trainObjectsCount = objectsCount * (percentageTrainValues/100.0);
         ui->CtextBrowser->append("Train objects: "  +  QString::number(trainObjectsCount) + "/" + QString::number(objectsCount));

         objects = database.getObjects();
         std::random_shuffle ( objects.begin(), objects.end());

         trainingObjects = std::vector<Object>(objects.begin(), objects.begin() + trainObjectsCount);
         canExecute = true;
     }
     ui->CpushButtonExecute->setEnabled(canExecute);
}

void MainWindow::on_CpushButtonExecute_clicked()
{
    int k = ui->CplainTextEditInputK->toPlainText().toInt();
    if (k >= objectsCount || k <= 0)
    {
        QMessageBox::warning(this, "Warning", "Value should be in range 0-" + objectsCount);
    }
    else
    {
        double percentage = 0;
        switch(ui->CcomboBoxClassifiers->currentIndex()) {
            case 0:
                percentage = classifierNN.Execute(trainingObjects, objects, k);
                break;
            case 1:
            percentage = classifierNM.Execute(trainingObjects, objects, k);
                break;
        }
        ui->CtextBrowser->append("Good classification: "  +  QString::number(percentage) + "%");
    }
}
