/src
    main.cpp

    /core
        Table.h/.cpp
        Column.h/.cpp
        Row.h/.cpp
        Cell.h/.cpp              # Съдържа DataType, не наследява типове

    /datatypes                
        DataType.h/.cpp          # Абстрактен базов клас
        TextType.h/.cpp          # Наследява DataType
        NumberType.h/.cpp        # Наследява DataType
        CurrencyType.h/.cpp      # Наследява DataType
        EGNType.h/.cpp          # Наследява DataType
        FacultyNumberType.h/.cpp # Наследява DataType
        TypeFactory.h/.cpp       # Factory за създаване на типове

    /csv
        CSVManager.h/.cpp
        CSVParser.h/.cpp       
        CSVWriter.h/.cpp
        CSVFormatter.h/.cpp      # за print

    /command
        Command.h                # Абстрактен базов клас
        CommandHistory.h/.cpp    #за undo
        SortCommand.h/.cpp
        FilterCommand.h/.cpp
        AddRowCommand.h/.cpp
        RemoveRowCommand.h/.cpp
        AddColumnCommand.h/.cpp
        EditCellCommand.h/.cpp

    /utils
        Validator.h/.cpp         # Валидация логика
        Exception.h/.cpp         # Собствени exceptions
        StringUtils.h/.cpp       # Помощни функции за strings

    /io                        
        CommandProcessor.h/.cpp  # Обработка на потребителски команди
        InputParser.h/.cpp       # Парсиране на команди
