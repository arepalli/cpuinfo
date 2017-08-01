# cpuinfo
Present the /proc/cpuinfo with Qt/Qml

## Dependencies
 * Qt/Qml 5.8 or later

## Build
```
Open cpuinfo.pro from the directory with QtCreator  
Run qmake
build
```

## Run
`Press run button on QtCreator`


# Development

### **CpuInfoModel:** Read the file and create a model
**cpuinfomodel.cpp**, which reads the **cpuinfo** data from the file /proc/cpuinfo and prepares a model for rendering.
**cpuinfo** data has a main part as **processor sections** and each section has **keys** and its information as **values**

### **cpuinfo:** 
**cpuinfo.qml** is a main page which contains a **CpuInfoListView** and a processor selection ComboBox.

### **CpuInfoListView:**
**CpuInfoListView.qml** is a list view which populates the **CpuInfoModel**

### **Section and list delegates:**
**SectionDelegate.qml** is a section delegate which presents processor number. This information is read from `CpuInfoModel.processor`
**CpuInfoListDelegate.qml** is a list item delegate which presents each row with the cpudata `CpuInfoModel.key` and `CpuInfoModel.values` with 2 columns

### **ColumnHelper.js**
A helper method `getMaxKeyWidth()` is implemented to provide the max key width which required to present the first column
