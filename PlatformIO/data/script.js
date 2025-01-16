var clockTable=[];
var clockTableExpanded = false;
var daysPickerNumber=0;
var hoursPickerNumber=0;
var minutesPickerNumber=0;
var modesPickerNumber=0;


window.onload=function() {
  getData();   
}

if (!!window.EventSource) {
var source = new EventSource('/events');

source.addEventListener('updateEvent', function(update) {
  console.log("updateEvent",update.data);
  getData();
}, false);   
}
 

//
// Handle click events from mode buttons
//
function handleModeClick(click) {
  let xhttp = new XMLHttpRequest();      
  if(click == "appMode1") {
    xhttp.open("GET", "appMode/set?appMode=1", false);
  }
  if(click == "appMode2") {
    xhttp.open("GET", "appMode/set?appMode=2", false);
  }
  if(click == "appMode3") {
    xhttp.open("GET", "appMode/set?appMode=3", false);
  }
  if(click == "appMode4") {
    xhttp.open("GET", "appMode/set?appMode=4", false);
  }
                  
  xhttp.send();
  handleResponse(xhttp.responseText);                  
}
  

// 
// Handle input events from temperature sliders
//
function handleSliderInput(input, value) {   
  if(input == "dayTime") {
    num=(value / 10).toFixed(1); 
    document.getElementById("setDayTimeItemText").innerHTML = num + " &#186C";
  }

  if(input == "nightTime") {
    num=(value / 10).toFixed(1); 
    document.getElementById("setNightTimeItemText").innerHTML = num + " &#186C";
  }

  if(input == "antiFreeze") {
    num=(value / 10).toFixed(1); 
    document.getElementById("setAntiFreezeItemText").innerHTML = num + " &#186C";
  }            
}  

//
// Handle change events from temperature sliders
//
function handleSliderChange(input, value) {
  let xhttp = new XMLHttpRequest(); 
    
  if(input == "dayTime") {
    xhttp.open("GET", "dayTimeTemp/set?dayTimeTemp=" + value, false);
  }

  if(input == "nightTime") {
    xhttp.open("GET", "nightTimeTemp/set?nightTimeTemp=" + value, false);
  }

  if(input == "antiFreeze") {
    xhttp.open("GET", "antiFreezeTemp/set?antiFreezeTemp=" + value, false);
  }      

  xhttp.send();
  handleResponse(xhttp.responseText);     
}


//
// Handle drop event from clock table
//
function handleClockTableDrop() {
  let xhttp = new XMLHttpRequest(); 

  console.log("handleClockTableDrop");
  if(clockTableExpanded == false){
    xhttp.open("GET", "clockTableLock/set?clockTableLock=ON", false);
  } else {
    xhttp.open("GET", "clockTableLock/set?clockTableLock=OFF", false);      
  }     

  xhttp.send();
  handleResponse(xhttp.responseText);
}
  

function getData() {
  let xhttp = new XMLHttpRequest();
     
  xhttp.open("GET", "currentTemp/get", false);
  xhttp.send();
  handleResponse(xhttp.responseText);

  xhttp.open("GET", "currentHumid/get", false);
  xhttp.send();
  handleResponse(xhttp.responseText);    
  
  xhttp.open("GET", "appMode/get", false);
  xhttp.send();
  handleResponse(xhttp.responseText);      
                  
  xhttp.open("GET", "dayTimeTemp/get", false);
  xhttp.send();
  handleResponse(xhttp.responseText);      

  xhttp.open("GET", "nightTimeTemp/get", false);
  xhttp.send();
  handleResponse(xhttp.responseText);      


  xhttp.open("GET", "antiFreezeTemp/get", false);
  xhttp.send(); 
  handleResponse(xhttp.responseText); 
    
  xhttp.open("GET", "clockTableLock/get", false);
  xhttp.send(); 
  handleResponse(xhttp.responseText);    
}


//
// Handling getting clockTable from server
//
function getClockTable() {
  let xhttp = new XMLHttpRequest();
    
  xhttp.open("GET", "clockTable/get", false);
  xhttp.send();
  handleResponse(xhttp.responseText);    
}


//
// Handling setting clockTable to server
//
function setClockTable() {
  let xhttp = new XMLHttpRequest();
     
  xhttp.open("GET", "clockTable/set", false);
  xhttp.send();
  handleResponse(xhttp.responseText);    
}
   

//
// Handle all responses for server
//
function handleResponse(response) {
  //
  // Handle response for appMode
  //
  if(response.search("appMode=") != -1){
    response=response.replace("appMode=", "");
    document.getElementById("selectDayTimeItemImage").contentDocument.getElementById("path1").style.fill="lightgrey";     
    document.getElementById("selectNightTimeItemImage").contentDocument.getElementById("path1").style.fill="lightgrey";     
    document.getElementById("selectAntiFreezeItemImage").contentDocument.getElementById("path1").style.fill="lightgrey";  
    document.getElementById("selectClockModeItemImage").contentDocument.getElementById("path1").style.fill="lightgrey";


    if(response == '1') {
      document.getElementById("selectDayTimeItemImage").contentDocument.getElementById("path1").style.fill="black";           
    }
    if(response == '2') {
      document.getElementById("selectNightTimeItemImage").contentDocument.getElementById("path1").style.fill="black";
    }
    if(response == '3') {
      document.getElementById("selectAntiFreezeItemImage").contentDocument.getElementById("path1").style.fill="black";
    }      
    if(response == '4') {
      document.getElementById("selectClockModeItemImage").contentDocument.getElementById("path1").style.fill="black";
    }       
  }
     
  //
  // Handle response for currentTemp
  //
  if(response.search("currentTemp=") != -1){
  response=response.replace("currentTemp=", "");
    num=(response / 10).toFixed(1);
    if(num.length == 3) {
      num=" " + num;
    }
    document.getElementById("currentTemperatureItemText").innerHTML = num + " &#186C";
  } 

  //
  // Handle response for currentHumid
  //
  if(response.search("currentHumid=") != -1){
    response=response.replace("currentHumid=", "");
    num=(response / 1).toFixed(0);
    document.getElementById("currentHumidityItemText").innerHTML = num + " %rh";
  }  
    

  //
  // Handle response for dayTimeTemp
  //
  if(response.search("dayTimeTemp=") != -1){
    response=response.replace("dayTimeTemp=", "");
    document.getElementById("setDayTimeItemSlider").value = response;     
    num=(response / 10).toFixed(1); 
    if(num.length == 3) {
      num=" " + num;
    }
    document.getElementById("setDayTimeItemText").innerHTML = num + " &#186C";
  }   


  //
  // Handle response for nightTimeTemp
  //
  if(response.search("nightTimeTemp=") != -1){
    response=response.replace("nightTimeTemp=", "");
    document.getElementById("setNightTimeItemSlider").value = response;         
    num=(response / 10).toFixed(1);   
    if(num.length == 3) {
      num ="  "+ num;
    }       
    document.getElementById("setNightTimeItemText").innerHTML = num + " &#186C";
  }


  //
  // Handle response for antiFreezeTemp
  //    
  if(response.search("antiFreezeTemp=") != -1){
    response=response.replace("antiFreezeTemp=", "");
    document.getElementById("setAntiFreezeItemSlider").value = response;         
    num=(response / 10).toFixed(1); 
    if(num.length == 3 ) {
      num="    " + num;
    }       
    document.getElementById("setAntiFreezeItemText").innerHTML = num + " &#186C";
  } 


  //
  // Handle response for clockTableLock
  //
  if(response.search("clockTableLock=") != -1){
    response=response.replace("clockTableLock=", "");        
    if(response == 'OFF') {
      // clockTable is free to use
      document.getElementById("setClockTableItemDrop").contentDocument.getElementById("path1").style.fill="black";
    } 
    if(response == 'ON') {
      // clockTable is not free to use
      document.getElementById("setClockTableItemDrop").contentDocument.getElementById("path1").style.fill="lightgrey";
    } 
      
    if(response == "OK"){
      if(clockTableExpanded == false){
        // clockTable is free and will be opened
        getClockTable();
        clockTableExpanded=true;
        const entry = document.getElementById("setClockTableItemDrop");
        entry.data="assets/colapseSign.svg";
      } else {
        // clockTable is free and will be closed
        setClockTable();
        clockTableExpanded=false;
        const entry = document.getElementById("setClockTableItemDrop");
        entry.data="assets/expandSign.svg";
      }
    }
  }


  //
  // Handle response for clockTableGet
  //
  if(response.search("getClockTable=") != -1) {
    response=response.replace("getClockTable=", "");
    var counter;
    var count;

    clockTable = [];
    responseArray = response.split(",");
    count = responseArray[0];
    for(counter=0;counter<count;counter++) {
      var entry={};      
      entry.day=responseArray[(counter * 4) + 1];
      entry.hour=responseArray[(counter * 4) + 2];
      entry.min=responseArray[(counter * 4) + 3];
      entry.mode=responseArray[(counter * 4) + 4];
      clockTable.push(entry);           
    }
    console.log(clockTable);
    fillClockTableEntries();
  }


  //
  // Handle response for clockTableSet
  //
  if(response.search("setClockTable=") != -1) {
    response=response.replace("setClockTable=", "");
    emptyClockTableEntries();       
  }
}



function fillClockTableEntries() {
  const container = document.getElementById("setClockTable");
  for(counter = 0;counter<clockTable.length;counter++){
    const entry = document.createElement("div");
    entry.id="clockTableEntry"+counter;
    entry.className="setClockTableEntryContainer";

    const entrySpacerDiv = document.createElement("div");
    entrySpacerDiv.id="entrySpacerDiv"+counter;
    entry.appendChild(entrySpacerDiv);      
        
    const entrySelectDiv = document.createElement("div");
    entrySelectDiv.id="entrySelectDiv"+counter; 
    entrySelectDiv.counter=counter;  
    entrySelectDiv.selected=false;   
    entrySelectDiv.style.textAlign="center";
    entrySelectDiv.onclick=function() {handleClockTableSelect(this)};
        
    const entrySelectImg = document.createElement("object");
    entrySelectImg.id="entrySelectImg"+counter;
    entrySelectImg.className="setClockTableEntrySelect";
    entrySelectImg.type="image/svg+xml";
    entrySelectImg.data="assets/unselectedSign.svg";
    entrySelectImg.style="pointer-events:none"; 
        
    entrySelectDiv.appendChild(entrySelectImg);
    entry.appendChild(entrySelectDiv);        

    const entryDayDiv = document.createElement("div");
    entryDayDiv.id="entryDayDiv"+counter;
    entryDayDiv.className="setClockTableEntryDay";
    switch(clockTable[counter].day) {
      case "1":
        entryDayDiv.innerHTML ="Monday";
        break;
      case "2":
        entryDayDiv.innerHTML ="Tuesday";
        break;
      case "3":
        entryDayDiv.innerHTML ="Wednesday";
        break;
      case "4":
        entryDayDiv.innerHTML ="Thursday";
        break;
      case "5":
        entryDayDiv.innerHTML ="Friday";
        break;
      case "6":
        entryDayDiv.innerHTML ="Saturday";
        break;  
      case "7":
        entryDayDiv.innerHTML ="Sunday";
        break;                                                                      
    }
    entry.appendChild(entryDayDiv);

    const entryTimeDiv = document.createElement("div");
    entryTimeDiv.id="entryTimeDiv"+counter;
    entryTimeDiv.className="setClockTableEntryTime";
    hour=clockTable[counter].hour;   
    if(hour.length == 1) hour ="0"+ hour;
    min=clockTable[counter].min;   
    if(min.length == 1) min ="0"+ min;        
    entryTimeDiv.innerHTML = hour + " : " + min;
    entry.appendChild(entryTimeDiv);        

    const entryModeDiv = document.createElement("div");
    entryModeDiv.id="entryModeDiv"+counter;
    entryModeDiv.style.textAlign="center";

    const entryModeImg = document.createElement("object");
    entryModeImg.id="entryModeImg"+counter;
    entryModeImg.className="setClockTableEntryMode";        
    entryModeImg.type="image/svg+xml";
    switch (clockTable[counter].mode) {
      case "1": 
        entryModeImg.data="assets/dayTime.svg";
        break;
      case "2": 
        entryModeImg.data="assets/nightTime.svg";
        break;
      case "3": 
        entryModeImg.data="assets/antiFreeze.svg";
        break;                        
    } 
    entryModeDiv.appendChild(entryModeImg);
    entry.appendChild(entryModeDiv); 

    container.appendChild(entry);   
  } 

  const actions = document.createElement("div");
  actions.id="clockTableAction";
  actions.className="setClockTableActionContainer";

  const actionSpacerDiv = document.createElement("div");
  actionSpacerDiv.id="actionSpacerDiv";
  actions.appendChild(actionSpacerDiv);      
        
  const actionEditDiv = document.createElement("div");
  actionEditDiv.id="actionEditDiv";   
  actionEditDiv.style.textAlign="center";
  actionEditDiv.style.display="inline-block";
  actionEditDiv.style.visibility="hidden";
  actionEditDiv.onclick=function() {handleClockTableActionEdit()};
        
  const actionEditImg = document.createElement("object");
  actionEditImg.id="actionEditImg";
  actionEditImg.className="setClockTableActionEdit";
  actionEditImg.type="image/svg+xml";
  actionEditImg.data="assets/editSign.svg";
  actionEditImg.style="pointer-events:none"; 

  actionEditDiv.appendChild(actionEditImg);
  actions.appendChild(actionEditDiv);

  const actionDeleteDiv = document.createElement("div");
  actionDeleteDiv.id="actionDeleteDiv";   
  actionDeleteDiv.style.textAlign="center";
  actionDeleteDiv.style.display="inline-block";
  actionDeleteDiv.style.visibility="hidden";
  actionDeleteDiv.onclick=function() {handleClockTableActionDelete()};
        
  const actionDeleteImg = document.createElement("object");
  actionDeleteImg.id="actionDeleteImg";
  actionDeleteImg.className="setClockTableActionDelete";
  actionDeleteImg.type="image/svg+xml";
  actionDeleteImg.data="assets/deleteSign.svg";
  actionDeleteImg.style="pointer-events:none"; 

  actionDeleteDiv.appendChild(actionDeleteImg);
  actions.appendChild(actionDeleteDiv); 
      
  const actionAddDiv = document.createElement("div");
  actionAddDiv.id="actionAddDiv";   
  actionAddDiv.style.textAlign="center";
  actionAddDiv.style.display="inline-block";
  actionAddDiv.style.visibility="visible";      
  actionAddDiv.onclick=function() {handleClockTableActionAdd()};
        
  const actionAddImg = document.createElement("object");
  actionAddImg.id="actionDeleteImg";
  actionAddImg.className="setClockTableActionDelete";
  actionAddImg.type="image/svg+xml";
  actionAddImg.data="assets/addSign.svg";
  actionAddImg.style="pointer-events:none"; 

  actionAddDiv.appendChild(actionAddImg);
  actions.appendChild(actionAddDiv);      

  container.appendChild(actions);    
}

function emptyClockTableEntries() {
  for(counter = 0;counter<clockTable.length;counter++){
    const entry = document.getElementById("clockTableEntry" + counter);
    if(entry != null) entry.remove();        
  }      
  entry = document.getElementById("clockTableAction");
  if(entry != null) entry.remove(); 
}

function handleClockTableSelect(clickedEntry){
  console.log("handleClockTableSelect: " + clickedEntry.counter);

  selectionMade=false;
  for(counter = 0;counter<clockTable.length;counter++){
    const entry=document.getElementById("entrySelectDiv"+counter);
    const entryImg=document.getElementById("entrySelectImg"+counter);
    if(entry.counter == clickedEntry.counter) {
      entry.selected=!entry.selected;
    } else {
      entry.selected=false;
    }
    if (entry.selected) {
      entryImg.data="assets/selectedSign.svg";
      selectionMade=true;
    } else {
      entryImg.data="assets/unselectedSign.svg";
    }
  }

  if (selectionMade) {
    var action=document.getElementById("actionEditDiv");
    action.style.visibility="visible";
    action=document.getElementById("actionDeleteDiv");
    action.style.visibility="visible";        
  } else {
    var action=document.getElementById("actionEditDiv");
    action.style.visibility="hidden";        
    action=document.getElementById("actionDeleteDiv");
    action.style.visibility="hidden";
   }
}

function handleClockTableActionEdit(){


}

function handleClockTableActionDelete(){
    

}

function handleClockTableActionAdd(){
  popupClockTableEntry=document.getElementById("popupClockTableEntry");
  popupClockTableEntry.style.display="block"; 
  addClockTableEntry=document.getElementById("addClockTableEntry");
  addClockTableEntry.style.display="block";       
}


function handleDaysPickerUpBtnClick() {
  daysPickerNumber++;
  if (daysPickerNumber>6) daysPickerNumber=6;
  daysPickerElement = document.getElementById("daysPickerContainer");
  daysPickerElement.style.transition="all 0.5s";  
  daysPickerElement.style.transform="translateY(" + (-40*daysPickerNumber) + "px)";
}

function handleDaysPickerDownBtnClick() {
  daysPickerNumber--;
  if (daysPickerNumber<0) daysPickerNumber=0;
  daysPickerElement = document.getElementById("daysPickerContainer");
  daysPickerElement.style.transition="all 0.5s";  
  daysPickerElement.style.transform="translateY(" + (-40*daysPickerNumber) + "px)";
}  


function handleHoursPickerUpBtnClick() {
  hoursPickerNumber++;
  if (hoursPickerNumber>23) hoursPickerNumber=23;
  hoursPickerElement = document.getElementById("hoursPickerContainer");
  hoursPickerElement.style.transition="all 0.5s";  
  hoursPickerElement.style.transform="translateY(" + (-40*hoursPickerNumber) + "px)";
}

function handleHoursPickerDownBtnClick() {
  hoursPickerNumber--;
  if (hoursPickerNumber<0) hoursPickerNumber=0;
  hoursPickerElement = document.getElementById("hoursPickerContainer");
  hoursPickerElement.style.transition="all 0.5s";
  hoursPickerElement.style.transform="translateY(" + (-40*hoursPickerNumber) + "px)";
}


function handleMinutesPickerUpBtnClick() {
  minutesPickerNumber++;
  if (minutesPickerNumber>11) minutesPickerNumber=11;
  minutesPickerElement = document.getElementById("minutesPickerContainer");
  minutesPickerElement.style.transition="all 0.5s";  
  minutesPickerElement.style.transform="translateY(" + (-40*minutesPickerNumber) + "px)";
}


function handleMinutesPickerDownBtnClick() {
  minutesPickerNumber--;
  if (minutesPickerNumber<0) minutesPickerNumber=0;
  minutesPickerElement = document.getElementById("minutesPickerContainer");
  minutesPickerElement.style.transition="all 0.5s";  
  minutesPickerElement.style.transform="translateY(" + (-40*minutesPickerNumber) + "px)";
}  


function handleModesPickerUpBtnClick() {
  modesPickerNumber++;
  if (modesPickerNumber>2) modesPickerNumber=2;
  modesPickerElement = document.getElementById("modesPickerContainer");
  modesPickerElement.style.transition="all 0.5s";  
  modesPickerElement.style.transform="translateY(" + (-40*modesPickerNumber) + "px)";
}


function handleModesPickerDownBtnClick() {
  modesPickerNumber--;
  if (modesPickerNumber<0) modesPickerNumber=0;
  modesPickerElement = document.getElementById("modesPickerContainer");
  modesPickerElement.style.transition="all 0.5s";
  modesPickerElement.style.transform="translateY(" + (-40*modesPickerNumber) + "px)";
} 