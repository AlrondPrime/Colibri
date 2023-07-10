#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(540, 346);

    // First column
    QLayout *first_column_layout = new QVBoxLayout();
    QWidget *first_column_widget = new QWidget();
    first_column_widget->setLayout(first_column_layout);
    first_column_layout->setSpacing(10);

    {
        QLabel *label = new QLabel("1. Configure input");
        label->setStyleSheet("font-weight: bold;");
        first_column_layout->addWidget(label);
    }

    // Select extensions for browse input file
    {
        LayoutWidget *boxV = new LayoutWidget(Qt::Vertical);

        QLabel *label = new QLabel("File extensions:");
        boxV->addWidget(label);
        input_file_lineedit = new QLineEdit();
        input_file_lineedit->setPlaceholderText("*.txt;*.png; etc..");
        boxV->addWidget(input_file_lineedit);

        first_column_layout->addWidget(boxV);
    }

    // Selecting output file
    {
        LayoutWidget *boxH = new LayoutWidget(Qt::Horizontal);
        LayoutWidget *boxV = new LayoutWidget(Qt::Vertical);

        QLabel *label = new QLabel("Selected file:");
        boxV->addWidget(label);

        input_file_lineedit = new QLineEdit();
        input_file_lineedit->setReadOnly(true);
        boxH->addWidget(input_file_lineedit);

        QPushButton *browse_input_button = new QPushButton("Browse");
        connect(browse_input_button, &QPushButton::clicked, this, &MainWindow::browseInputFiles);
        boxH->addWidget(browse_input_button);

        boxV->addWidget(boxH);
        first_column_layout->addWidget(boxV);
    }

    // Variable to perform XOR operation
    {
        LayoutWidget *boxV = new LayoutWidget(Qt::Vertical);

        QLabel *label = new QLabel("Set variable to perform conversion:");
        boxV->addWidget(label);

        spinbox = new QSpinBox();
        boxV->addWidget(spinbox);
        spinbox->setMinimum(0);
        spinbox->setMaximum(255);

        first_column_layout->addWidget(boxV);
    }

    // What to do if output file exists
    {
        LayoutWidget *boxV = new LayoutWidget(Qt::Vertical);

        // Action if output file already exists
        QLabel *label = new QLabel("Action if output file already exists:");
        boxV->addWidget(label);

        action_if_exists = new QComboBox();
        action_if_exists->addItem("Overwrite");
        action_if_exists->addItem("Increment filename");
        boxV->addWidget(action_if_exists);

        first_column_layout->addWidget(boxV);
    }

    // Timer for input file
    {
        LayoutWidget *boxV = new LayoutWidget(Qt::Vertical);

        timer_checkbox = new QCheckBox("Enable timer");
        connect(timer_checkbox, &QCheckBox::stateChanged, this, &MainWindow::timerCheckboxToggled);
        boxV->addWidget(timer_checkbox);

        time_edit = new QTimeEdit();
        time_edit->setDisabled(true);
        boxV->addWidget(time_edit);

        first_column_layout->addWidget(boxV);
    }

    // Whether to delete input file
    remove_checkbox = new QCheckBox("Remove input file after convertion");
    first_column_layout->addWidget(remove_checkbox);


    // Second column
    QLayout *second_column_layout = new QVBoxLayout();
    QWidget *second_column_widget = new QWidget();
    second_column_layout->setSpacing(10);
    second_column_widget->setLayout(second_column_layout);

    {
        QLabel *label = new QLabel("2. Configure output");
        label->setStyleSheet("font-weight: bold;");
        second_column_layout->addWidget(label);
    }

    // Selecting output file
    {
        LayoutWidget *boxH = new LayoutWidget(Qt::Horizontal);
        LayoutWidget *boxV = new LayoutWidget(Qt::Vertical);

        QLabel *label = new QLabel("Selected file:");
        boxV->addWidget(label);

        output_file_lineedit = new QLineEdit();
        output_file_lineedit->setReadOnly(true);
        boxH->addWidget(output_file_lineedit);

        QPushButton *browse_output_button = new QPushButton("Browse");
        connect(browse_output_button, &QPushButton::clicked, this, &MainWindow::browseOutputFiles);
        boxH->addWidget(browse_output_button);

        boxV->addWidget(boxH);
        second_column_layout->addWidget(boxV);
    }

    {
        QSplitter *splitter = new QSplitter(Qt::Vertical);
        splitter->showMaximized();
        second_column_layout->addWidget(splitter);
    }

    {
        QLabel *label = new QLabel("3. Start procedure");
        label->setStyleSheet("font-weight: bold;");
        second_column_layout->addWidget(label);
    }

    {
        QPushButton *convert_button = new QPushButton("Convert!");
        connect(convert_button, &QPushButton::clicked, this, &MainWindow::startConvertion);
        second_column_layout->addWidget(convert_button);
    }

    // Central widget
    {
        QLayout *central_layout = new QHBoxLayout();
        QWidget *central_widget = new QWidget();
        central_widget->setLayout(central_layout);
        central_layout->addWidget(first_column_widget);

        QSplitter *splitter = new QSplitter(Qt::Horizontal);
        splitter->setFixedHeight(40);
        central_layout->addWidget(splitter);

        central_layout->addWidget(second_column_widget);

        setCentralWidget(central_widget);
    }
}

MainWindow::~MainWindow()
{
}

