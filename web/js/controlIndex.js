/*

var c = document.getElementById("miCanvas");
var ancho = c.width;
var altura = c.height;

var ctx = c.getContext("2d");
// graficar el circulo
ctx.beginPath();
var n = 0;
var array = [];

function insertData(){

  // variables globales
  var h_center,k_center, str ;
  // root center(h,k)
  h_center = 250;
  k_center = 75;

  var str = document.getElementById("txtInsert").value;  // para tamaño de letra <5
  var bool = -1;

  console.log("length: "+ array.length);
  array[array.length] = str;

  // para los hijos

  for(var i = 0; i < array.length; i++){
      if(i === 0){

        ctx.fillStyle = "#3498DB";
        ctx.strokeStyle = "black";
        ctx.font = "20px Georgia";
        ctx.lineWidth = 10;
        ctx.arc(h_center, k_center, 35, 0, 2 * Math.PI, false);
        ctx.fill();
        // escribir texto dentro del circulo
        ctx.beginPath();
        ctx.fillStyle = "black";
        // str = "casa";
        // llenar texto en cir
        ctx.fillText(str, (h_center - str.length*4), k_center+4);

      }else {

        if((i % 2) === 0){

          hijoDerecho(array[i],h_center +50,k_center +50);
        }else{
          hijoIzquierdo(array[i],h_center,k_center +50);
        }
      }
  }
  document.getElementById("txtInsert").value ="";


}

function hijoDerecho(str, h, k){
  // graficar el circulo
  ctx.beginPath();
  ctx.fillStyle = "#3498DB";
  ctx.strokeStyle = "black";
  ctx.font = "20px Georgia";
  ctx.lineWidth = 10;

  h_center = h+100;
  k_center = k+100;
  ctx.arc(h_center, k_center, 35, 0, 2 * Math.PI, false);
  ctx.fill();

  // escribir texto dentro del circulo
  ctx.beginPath();
  ctx.fillStyle = "black";
  var str = document.getElementById("txtInsert").value;  // para tamaño de letra <5

  // str = "casa";
  ctx.fillText(str, (h_center - str.length*4), k_center+4); // llenar texto en cir
}

function hijoIzquierdo(str, h, k){
  // graficar el circulo
  ctx.beginPath();
  ctx.fillStyle = "#3498DB";
  ctx.strokeStyle = "black";
  ctx.font = "20px Georgia";
  ctx.lineWidth = 10;

  h_center = h-100;
  k_center = k+100;
  ctx.arc(h_center, k_center, 35, 0, 2 * Math.PI, false);
  ctx.fill();

  // escribir texto dentro del circulo
  ctx.beginPath();
  ctx.fillStyle = "black";
  var str = document.getElementById("txtInsert").value;  // para tamaño de letra <5

  // str = "casa";
  ctx.fillText(str, (h_center - str.length*4), k_center+4); // llenar texto en cir
}


 //dibujar un nodo enlazado con su hijo

 function dibuja_flecha(from, to){

    var radianes = Math.PI/100;
    var headlen = 10;
    console.log(from.x+" , "+to.y);
    var angle = Math.atan(Math.abs(from.y - to.y) / Math.abs(from.x - to.x));
    var rise = 25*Math.sin(angle);
    var run = 25*Math.cos(angle);

 //   var rise = from.r * Math.sin(angle);
 //   var run = to.r * Math.cos(angle);

    // var canvas = document.getElementById('myCanvas');
    // var context = canvas.getContext('2d');

    ctx.beginPath();
    ctx.lineWidth=2;

    if (from.x < to.x) {
       from.x += run;
       to.x -= run;
    } else {
       from.x -= run;
       to.x += run;
    }
    if (from.y < to.y) {
       from.y += rise;
       to.y -= rise;
    } else {
        from.y -= rise;
        to.y += rise;
    }
    ctx.moveTo(from.x, from.y);
    ctx.lineTo(to.x, to.y);
    ctx.stroke();

    ctx.moveTo(to.x, to.y);
    ctx.lineTo(to.x - headlen * Math.cos(angle - Math.PI / 6), to.y - headlen * Math.sin(angle - Math.PI / 6));
    ctx.moveTo(to.x, to.y);
    ctx.lineTo(to.x - headlen * Math.cos(angle + Math.PI / 6), to.y - headlen * Math.sin(angle + Math.PI / 6));
    ctx.stroke();

 }

// dibujar nodo

function dibuja_Nodo(str, h, k){

  ctx.beginPath();
  ctx.fillStyle = "#3498DB";
  ctx.strokeStyle = "black";
  ctx.font = "12px Georgia";
  ctx.lineWidth = 10;

  h_center = h;
  k_center = k;
  ctx.arc(h_center, k_center, 25, 0, 2 * Math.PI, false); //radio
  ctx.fill();

  // escribir texto dentro del circulo
  ctx.beginPath();
  ctx.fillStyle = "black";
  // var str = document.getElementById("txtInsert").value;  // para tamaño de letra <5

  // str = "casa";
  ctx.fillText(str, (h_center - str.length*4), k_center+4);
}
*/

var txtAdd = document.getElementById("txtInsert");
txtAdd.addEventListener("keydown", function (e) {
    if (e.keyCode === 13) {
        //(e);
        enviar();
    }
});

var txtSearch = document.getElementById("txtSearch");
txtSearch.addEventListener("keydown", function (e) {
    if (e.keyCode === 13) {
        //(e);
        buscar();
    }
});

var txtDelete = document.getElementById("txtDelete");
txtDelete.addEventListener("keydown", function (e) {
    if (e.keyCode === 13) {
        //(e);
        eliminar();
    }
});
/* ============== FUNCIONES PARA DIBUJAR CON D3  =============================== */


var dato, animDuration=500;

var data = [
    { "valor" : "Level 2: A","id" : "Level 2: A", "padre":"Top Level" },
    { "valor" : "Top ","id" : "Top Level", "padre":"" },
    { "valor" : "Son of A","id" : "Son of A", "padre":"Level 2: A" },
    { "valor" : "Daughter of A","id" : "Daughter of A", "padre":"Level 2: A" },
    { "valor" : "Level 2:B","id" : "Level 2: B", "padre":"Top Level" }
    ];

function dibujarTree(tree){

    data = tree;

  /* data = [
   {"valor":"","id":"0x7f12500011f0","padre":""},
   {"valor":"D","id":"0x7f12500066d0","padre":"0x7f12500011f0"},];*/

   // console.log(data);
// *********** Convertir dato plano en un arbol con jerarquia ***************

// crear un nombre: nodo map
var dataMap = data.reduce(function(map, node) {
  map[node.id] = node;
  return map;
}, {});

// crea el arbol array
var treeData = [];

data.forEach(function(node) {
  // agrega a su padre
  var padre = dataMap[node.padre];
  if (padre) {
    // crea un array hijo si no existe
    (padre.children || (padre.children = []))
      // add node to child array
      .push(node);
  } else {
    // parent is null or missing
    treeData.push(node);
  }
});

// ************** Generar el diagrama del Arbol  *****************
var margin = {top: 20, right: 120, bottom: 20, left: 120},
 width = 960 - margin.right - margin.left,
 height = 500 - margin.top - margin.bottom;
// var border = 2;
// var bordercolor='black';
var i = 0,root;

var tree = d3.layout.tree()
 .size([height, width]);

var diagonal = d3.svg.diagonal() // buscar remplazar con una linea
 .projection(function(d) { return [d.x, d.y]; }); // cambio

 // var svg = d3.select("body").remove();
 var svg = d3.select("body").append("svg")
 .attr("width", width + margin.right + margin.left)
 .attr("height", height + margin.top + margin.bottom)
 // .attr("border",border)
 .attr("class", "svg")
  .append("g")
 .attr("transform", "translate(" + margin.left + "," + margin.top + ")");

function test(tree){
  var arr = tree;
  return arr;
}
// console.log("<<"+test[0]);

root = treeData[0];
dato = treeData[0];;
// console.log(JSON.stringify(root));

update(root);

function update(source) {

  // Calcular el nuevo arbol.
  var nodes = tree.nodes(root).reverse(),
   links = tree.links(nodes);

  // Normaliza para el camino fijado
  nodes.forEach(function(d) { d.y = d.depth * 100; });// cambio de 180 a 100

  // Declarar el nodo¦
  var node = svg.selectAll("g.node")
   .data(nodes, function(d) { return d.id || (d.id = ++i); });

  // Agregar los nodos.
  var nodeEnter = node.enter().append("g")
   .attr("class", "node")
   .attr("transform", function(d) {
    //
    // return "translate(" + d.y + "," + d.x + ")"; });
    return "translate(" + d.x + "," + d.y + ")"; }) // cambio vertical
   .attr("id",function(d){return "node-"+d.id});

   // Agregar circulos
  nodeEnter.append("circle")
   .attr("r", 10)
   .style("fill", function(d) { return d.isword ==="1" ? "#abebc6" : "#fff"; });
   // .style("fill", "#fff");

   // .style("fill", function(d) { return d._children ? "#48c9b0" : "#fff"; });

   // agreagar texto a los circulos
  nodeEnter.append("text")
   .attr("y", function(d) {
    // return -2})
    return d.children || d._children ? -18 : 18; })
   .attr("dy", ".35em")
   .attr("text-anchor", "middle")
   .text(function(d) { return d.valor; })
   .style("fill-opacity", 1);

/*
  nodeEnter.append("text")
   .attr("x", function(d) {
    return d.children || d._children ? -13 : 13; })
   .attr("dy", ".35em")
   .attr("text-anchor", function(d) {
    return d.children || d._children ? "end" : "start"; })
   .text(function(d) { return d.valor; })
   .style("fill-opacity", 1);
*/
  // Declarar el enlace de camino¦
  var link = svg.selectAll("path.link")
   .data(links, function(d) { return d.target.id; });

  // agregar el enlace
  link.enter().insert("path", "g")
   .attr("class", "link")
   .attr("d", diagonal);
   // .attr("d",function(d){
   //    return d.source.id +"->"+ d.target.id;
   //  })

}

}

/*----------------------------------------------------------------------------------*/

function visitElement(element,animX){
 // d3.select("#node-"+element.id).classed("visited",true);
 // console.log("->"+element.valor);
  d3.select("#node-"+element.id)
    .transition().duration(animDuration).delay(animDuration*animX)
    .style("fill","#FF5733").style("stroke","#FF5733");
}

function dft(){
  var stack=[];
  var animX=0;
  var root = dato;
  stack.push(root);

  // console.log(stack.length!==0);
  while(stack.length!==0){
    var element = stack.pop();
     visitElement(element,animX);
      animX=animX+1;
    if(element.children!==undefined){
      for(var i=0; i<element.children.length; i++){
        stack.push(element.children[element.children.length-i-1]);
        console.log("element: "+element.children[element.children.length-i-1].valor);
      }
    }

  }
  imprimir();
  console.log("log-->");
}

function bft(){
  var queue=[];
  var animX=0;
  queue.push(root);

  while(queue.length!==0){

    var element = queue.shift();

    visitElement(element,animX);

    animX= animX+1;

    if(element.children!==undefined){
      for(var i=0; i<element.children.length; i++){
        queue.push(element.children[i]);
        console.log(element.children[i].valor);
      }
    }
  }
}



/* ============== FUNCIONES PARA SERVER SET && GET  =============================== */
/**
 * funcion get para el recibir datos
 */
function handleClick(event){

    //obtener el texto
    var str = document.getElementById("txtInsert").value;

    console.log("input: "+str);

    var http = new XMLHttpRequest();
    var url = 'http://localhost:8091/radix';
    var params = 'orem=ipsum&name=binny';
    http.open('GET', url, true);

    http.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');

    http.onreadystatechange = function() {
        if(http.readyState == 4 && http.status == 200) {
            console.log(http.responseText);
            alert(http.responseText);

        }
    }
    http.send(params);
}

/**------------- ENVIAR GET STRING ----------------- */
function validar() {
    if (document.getElementById("txtInsert").value== "") {
        alert("Enter a text");
        document.getElementById("txtInsert").focus();
        return false;
    }
    if (!/^[a-zA-Z]*$/g.test(document.getElementById("txtInsert").value)) {
        alert("Invalid characters");
        document.getElementById("txtInsert").focus();
        return false;
    }
}
/**------------- ENVIAR GET STRING ----------------- */
function enviar(){

  //obtener el texto
  var str = document.getElementById("txtInsert").value;
  str = str.replace(/\s/g, "");

  if (str== "") {
        alert("Enter a text");
        document.getElementById("txtInsert").focus();

    }
    else{
    if (!/^[a-zA-Z]*$/g.test(str)) {
        alert("Invalid characters");
        document.getElementById("txtInsert").focus();

    }
    else{


    str = str.split(' ').join('');

  // console.log("input: "+str);

  document.getElementById('txtInsert').value = ''

  var http = new XMLHttpRequest();
  var url = 'http://localhost:8091/radix/getTree?word='+str.toUpperCase();
  var params = 'orem=ipsum&name=binny';
  http.open('GET', url, true);

  http.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');

  http.onreadystatechange = function() {
      if(http.readyState == 4 && http.status == 200) {
          // respuesta del servidor en array
          // console.log(http.responseText);
          // alert(http.responseText);
          var arr = JSON.parse(http.responseText)["tree"];
          // alert(http.responseText);

          /*
           var padre = {x:ancho/2, y:50};
           var hijo = {x:ancho/2,y:50};
           var h = ancho / 2;
           var k = 50;
           var coord_Node = [];
           for(var i = 0; i < arr.length; i++){

              dibuja_Nodo(arr[i].valor,h, k+(50*i));
           }
          */
           //
           // var id = ""


           // console.log("stringify arr->"+JSON.stringify(arr));
            d3.selectAll("svg").remove(); // eliminar el anterior y reemplazar
           dibujarTree(arr);



           // var svg = d3.select("body").remove();

           /*// console.log(arr[i].id);
            if(arr.length === 1) dibuja_Nodo(arr[0].valor, padre.x,padre.y);
            else{

              dibuja_Nodo(arr[0].valor, h, k);
              coord_Node.push({x:h, y:k, num:1, nivel:0});


              for(var i = 1; i < arr.length; i++){

                // id = arr[i].id;
                for(var j = 0; j < i; j++){

                  // console.log(arr[i].valor+" --> id: "+arr[i].id+" padre:"+arr[i].padre);

                  if(arr[i].padre === arr[j].id ){

                    console.log(" ---> "+coord_Node[j]);
                    var node_h = coord_Node[j].x - (50*coord_Node[j].num);
                    var node_k = coord_Node[j].y - (50*coord_Node[j].nivel);

                    coord_Node[i] = {x:node_h, y:node_k, num:1, nivel:0};

                    dibuja_Nodo(arr[i].valor,node_h,node_k);
                    dibuja_flecha(coord_Node[j],coord_Node[i]);

                    coord_Node[i].num =  coord_Node[i].num + 1;
                    // falta numero de hijos y numero de niveles
                  }
                }
              }
            }         */

      }
  }
  http.send(params);

}
}

}

/** --------------- BUSCAR UNA PALABRA DENTRO DEL ARBOL ----------------**/

function buscar(){

  //obtener el texto
    var str = document.getElementById("txtSearch").value;

    document.getElementById("txtSearch").value="";
    // console.log("input: "+str);

    var http = new XMLHttpRequest();
    var url = 'http://localhost:8091/radix/find?word='+ str.toUpperCase();
    var params = 'orem=ipsum&name=binny';
    http.open('GET', url, true);

    http.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');

    http.onreadystatechange = function() {
        if(http.readyState == 4 && http.status == 200) {


            if(http.responseText ==="1"){

              document.getElementById('label1').innerHTML = 'WORD: \"'+str.toUpperCase() +'\" FOUND';

            }else{

              document.getElementById('label1').innerHTML = 'WORD: \"'+str.toUpperCase()+ '\" NOT FOUND';

            }


        }
    }
    http.send(params);

}

/** --------------- BUSCAR UNA PALABRA DENTRO DEL ARBOL ----------------**/

function eliminar(){


  //obtener el texto
    var str = document.getElementById("txtDelete").value;
    str = str.split(' ').join('');

    if(str !=="" ){

      document.getElementById("txtDelete").value = "";
      // console.log("input Delete: "+str);

      var http = new XMLHttpRequest();
      var url = 'http://localhost:8091/radix/delete?word='+ str.toUpperCase();
      var params = 'orem=ipsum&name=binny';
      http.open('GET', url, true);

      http.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');

      http.onreadystatechange = function() {
        if(http.readyState == 4 && http.status == 200) {

          document.getElementById('label1').innerHTML = "To delete: "+str;
          // get response in an array
          var arr = JSON.parse(http.responseText)["tree"];
          // draw the graph
          d3.selectAll("svg").remove(); // eliminar el anterior y reemplazar
          dibujarTree(arr);

        }
      }
      http.send(params);
    }

}

/* ---------------------------  LIMPAR EL ARBOL F5-----------------------------*/

function clear(){

  var http = new XMLHttpRequest();
  var url = 'http://localhost:8091/radix/clear';
  var params = 'orem=ipsum&name=binny';
  http.open('GET', url, true);

  http.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');

  http.onreadystatechange = function() {
      if(http.readyState == 4 && http.status == 200) {
          console.log(http.responseText);
          // alert(http.responseText);

      }
  }
  http.send(params);

}


/* ---------------------------  PRINT DEL ARBOL DFS-----------------------------*/
// var lista=[];

function imprimir(){

    var http = new XMLHttpRequest();
    var url = 'http://localhost:8091/radix/printf';
    var params = 'orem=ipsum&name=binny';
    http.open('GET', url, true);

    http.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');

    http.onreadystatechange = function() {
        if(http.readyState == 4 && http.status == 200) {

            var array = JSON.parse(http.responseText)["list"];
            console.log("::> "+http.responseText);
            // console.log("0: "+array[0].word);
            var arr_i = "Printf: ";
            for(var  i = 0; i < array.length; i++){
              arr_i += (array[i].word+", ");
            }
            document.getElementById("label1").innerHTML = arr_i;

        }
    }
    http.send(params);

}
