const express = require("express");
const cors = require("cors");
const { exec } = require("child_process");
const fs = require("fs");

const app = express();
const PORT = 3001;

app.use(
  cors({
    origin: "http://localhost:2303",
    methods: ["GET", "POST", "OPTIONS"],
    allowedHeaders: ["Content-Type"],
    credentials: true,
  })
);
app.use(express.json({ limit: "20mb" }));

app.post("/api/print", (req, res) => {
  const objData = req.body.obj;
  const targetVertices = req.body.targetVertices;

  const inputPath = "temp_input.obj";
  const outputPath = "temp_input_remesh.obj";

  fs.writeFileSync(inputPath, objData);

  const comando = `quadric_remeshing.exe ${inputPath} ${outputPath} ${targetVertices}`;
  console.log("Ejecutando comando:", comando);

  exec(comando, (err, stdout, stderr) => {
    if (err) {
      console.error("Error al ejecutar quadric_remeshing.exe:", stderr);
      return res
        .status(500)
        .json({ error: "Error al ejecutar quadric_remeshing.exe" });
    }

    let salida;
    try {
      salida = fs.readFileSync(outputPath, "utf-8");
    } catch (e) {
      return res.status(500).json({ error: "Error al leer archivo de salida" });
    }

    try {
      fs.unlinkSync(inputPath);
    } catch (e) {
      console.warn("input bloqueado");
    }
    try {
      fs.unlinkSync(outputPath);
    } catch (e) {
      console.warn("output bloqueado");
    }

    res.json({
      stdout: stdout.trim(),
      obj: salida,
    });

    console.log("quadric_remeshing.exe ejecutado correctamente");
  });
});
app.post("/api/voronoi", (req, res) => {
  const objData = req.body.obj;
  const nombre = req.body.nombre || "modelo";
  const modo = parseInt(req.body.modo); // debe ser 0, 1, 2, 3
  const numCluster = parseInt(req.body.targetVertices) || 20000;

  if (![0, 1, 2, 3].includes(modo)) {
    return res
      .status(400)
      .json({ error: "Modo inválido. Debe ser 0, 1, 2 o 3." });
  }

  const inputPath = `${nombre}.obj`;
  const outputPath = `${nombre}_out.obj`;

  fs.writeFileSync(inputPath, objData);

  const comando = `quadratic_remesh.exe ${modo} ${inputPath} ${outputPath} ${numCluster}`;
  console.log("Ejecutando comando:", comando);

  exec(comando, (err, stdout, stderr) => {
    if (err) {
      console.error("Error al ejecutar quadratic_remesh.exe:", stderr);
      return res
        .status(500)
        .json({ error: "Error al ejecutar quadratic_remesh.exe" });
    }

    let salida;
    try {
      salida = fs.readFileSync(outputPath, "utf-8");
    } catch (e) {
      console.error("No se pudo leer el archivo de salida");
      return res.status(500).json({ error: "Error al leer archivo de salida" });
    }

    // Limpieza de archivos temporales
    try {
      fs.unlinkSync(inputPath);
    } catch (e) {
      console.warn("No se pudo eliminar input");
    }
    try {
      fs.unlinkSync(outputPath);
    } catch (e) {
      console.warn("No se pudo eliminar output");
    }

    res.json({
      stdout: stdout.trim(),
      obj: salida,
    });

    console.log("quadratic_remesh.exe ejecutado correctamente");
  });
});

app.listen(PORT, () => {
  console.log(`Servidor backend escuchando en http://localhost:${PORT}`);
});
