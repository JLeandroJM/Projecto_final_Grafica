<template>
  <div class="min-h-screen bg-gradient-to-br from-slate-900 to-slate-800 text-white">
    <!-- Header -->
    <header class="bg-slate-800/50 backdrop-blur-sm border-b border-slate-700 p-4">
      <h1 class="text-3xl font-bold text-center bg-gradient-to-r from-blue-400 to-purple-400 bg-clip-text text-transparent">
        Visualizador de Ángulos 3D
      </h1>
      <p class="text-center text-slate-300 mt-2">Explora las transformaciones geométricas en tiempo real</p>
    </header>

    <div class="container mx-auto p-6">
      <div class="grid lg:grid-cols-3 gap-6">
        <!-- Panel de Control -->
        <div class="lg:col-span-1 space-y-6">
          <!-- Controles de Rotación -->
          <div class="bg-slate-800/50 backdrop-blur-sm rounded-xl p-6 border border-slate-700">
            <h3 class="text-xl font-semibold mb-4 flex items-center">
              <RotateCcw class="w-5 h-5 mr-2 text-blue-400" />
              Rotación (Grados)
            </h3>
            
            <div class="space-y-4">
              <div>
                <label class="block text-sm font-medium mb-2">Eje X (Pitch)</label>
                <input 
                  v-model.number="rotation.x" 
                  type="range" 
                  min="0" 
                  max="360" 
                  class="w-full h-2 bg-slate-700 rounded-lg appearance-none cursor-pointer slider"
                >
                <span class="text-sm text-slate-400">{{ rotation.x }}°</span>
              </div>
              
              <div>
                <label class="block text-sm font-medium mb-2">Eje Y (Yaw)</label>
                <input 
                  v-model.number="rotation.y" 
                  type="range" 
                  min="0" 
                  max="360" 
                  class="w-full h-2 bg-slate-700 rounded-lg appearance-none cursor-pointer slider"
                >
                <span class="text-sm text-slate-400">{{ rotation.y }}°</span>
              </div>
              
              <div>
                <label class="block text-sm font-medium mb-2">Eje Z (Roll)</label>
                <input 
                  v-model.number="rotation.z" 
                  type="range" 
                  min="0" 
                  max="360" 
                  class="w-full h-2 bg-slate-700 rounded-lg appearance-none cursor-pointer slider"
                >
                <span class="text-sm text-slate-400">{{ rotation.z }}°</span>
              </div>
            </div>

            <div class="mt-4 flex gap-2">
              <button 
                @click="resetRotation" 
                class="px-4 py-2 bg-slate-700 hover:bg-slate-600 rounded-lg text-sm transition-colors"
              >
                Reset
              </button>
              <button 
                @click="randomRotation" 
                class="px-4 py-2 bg-blue-600 hover:bg-blue-500 rounded-lg text-sm transition-colors"
              >
                Aleatorio
              </button>
            </div>
          </div>

          <!-- Información de Ángulos -->
          <div class="bg-slate-800/50 backdrop-blur-sm rounded-xl p-6 border border-slate-700">
            <h3 class="text-xl font-semibold mb-4 flex items-center">
              <Calculator class="w-5 h-5 mr-2 text-green-400" />
              Información Angular
            </h3>
            
            <div class="space-y-3 text-sm">
              <div class="flex justify-between">
                <span class="text-slate-400">Radianes X:</span>
                <span class="font-mono">{{ toRadians(rotation.x).toFixed(3) }}</span>
              </div>
              <div class="flex justify-between">
                <span class="text-slate-400">Radianes Y:</span>
                <span class="font-mono">{{ toRadians(rotation.y).toFixed(3) }}</span>
              </div>
              <div class="flex justify-between">
                <span class="text-slate-400">Radianes Z:</span>
                <span class="font-mono">{{ toRadians(rotation.z).toFixed(3) }}</span>
              </div>
              <hr class="border-slate-600">
              <div class="flex justify-between">
                <span class="text-slate-400">Magnitud:</span>
                <span class="font-mono">{{ magnitude.toFixed(3) }}</span>
              </div>
              <div class="flex justify-between">
                <span class="text-slate-400">Vector Unitario:</span>
                <span class="font-mono text-xs">{{ unitVector }}</span>
              </div>
            </div>
          </div>

          <!-- Controles de Visualización -->
          <div class="bg-slate-800/50 backdrop-blur-sm rounded-xl p-6 border border-slate-700">
            <h3 class="text-xl font-semibold mb-4 flex items-center">
              <Eye class="w-5 h-5 mr-2 text-purple-400" />
              Visualización
            </h3>
            
            <div class="space-y-3">
              <label class="flex items-center">
                <input v-model="showAxes" type="checkbox" class="mr-2">
                <span class="text-sm">Mostrar Ejes</span>
              </label>
              <label class="flex items-center">
                <input v-model="showGrid" type="checkbox" class="mr-2">
                <span class="text-sm">Mostrar Grilla</span>
              </label>
              <label class="flex items-center">
                <input v-model="autoRotate" type="checkbox" class="mr-2">
                <span class="text-sm">Rotación Automática</span>
              </label>
            </div>
          </div>

          <!-- Carga de Archivo OBJ -->
          <div class="bg-slate-800/50 backdrop-blur-sm rounded-xl p-6 border border-slate-700">
            <h3 class="text-xl font-semibold mb-4 flex items-center">
              <Upload class="w-5 h-5 mr-2 text-yellow-400" />
              Cargar Modelo 3D
            </h3>
            
            <div class="space-y-4">
              <div class="border-2 border-dashed border-slate-600 rounded-lg p-4 text-center">
                <input 
                  ref="fileInput"
                  type="file" 
                  accept=".obj"
                  @change="loadObjFile"
                  class="hidden"
                >
                <button 
                  @click="$refs.fileInput.click()"
                  class="w-full py-2 px-4 bg-yellow-600 hover:bg-yellow-500 rounded-lg transition-colors"
                >
                  Seleccionar archivo .obj
                </button>
                <p class="text-xs text-slate-400 mt-2">Formatos soportados: .obj</p>
              </div>
              
              <div v-if="currentModel.name" class="bg-slate-700 rounded-lg p-3">
                <div class="flex justify-between items-center">
                  <span class="text-sm font-medium">{{ currentModel.name }}</span>
                  <button 
                    @click="resetToDefaultCube"
                    class="text-xs text-slate-400 hover:text-white"
                  >
                    Usar cubo por defecto
                  </button>
                </div>
                <div class="text-xs text-slate-400 mt-1">
                  Vértices: {{ currentModel.vertices.length }} | Caras: {{ currentModel.faces.length }}
                </div>
              </div>
            </div>
          </div>
        </div>

        <!-- Visualizador 3D -->
        <div class="lg:col-span-2">
          <div class="bg-slate-800/50 backdrop-blur-sm rounded-xl p-6 border border-slate-700 h-[600px]">
            <div class="relative w-full h-full bg-slate-900 rounded-lg overflow-hidden">
              <canvas 
                ref="canvas" 
                class="w-full h-full cursor-grab active:cursor-grabbing"
                @mousedown="startDrag"
                @mousemove="drag"
                @mouseup="endDrag"
                @mouseleave="endDrag"
                @wheel="zoom"
              ></canvas>
              
              <!-- Overlay de información -->
              <div class="absolute top-4 left-4 bg-black/50 backdrop-blur-sm rounded-lg p-3 text-xs">
                <div>Posición: ({{ rotation.x }}, {{ rotation.y }}, {{ rotation.z }})</div>
                <div>Zoom: {{ (scale * 100).toFixed(0) }}%</div>
                <div class="text-slate-400 mt-1">Arrastra para rotar • Scroll para zoom</div>
              </div>
            </div>
          </div>

          <!-- Matriz de Transformación -->
          <div class="mt-6 bg-slate-800/50 backdrop-blur-sm rounded-xl p-6 border border-slate-700">
            <h3 class="text-xl font-semibold mb-4 flex items-center">
              <Grid3X3 class="w-5 h-5 mr-2 text-orange-400" />
              Matriz de Transformación
            </h3>
            
            <div class="grid grid-cols-4 gap-2 font-mono text-sm">
              <div v-for="(value, index) in transformMatrix" :key="index" 
                   class="bg-slate-700 p-2 rounded text-center">
                {{ value.toFixed(3) }}
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script setup>
import { ref, onMounted, onUnmounted, computed, watch } from 'vue'
import { RotateCcw, Calculator, Eye, Grid3X3, Upload } from 'lucide-vue-next'

// Estado reactivo
const canvas = ref(null)
const rotation = ref({ x: 45, y: 30, z: 0 })
const scale = ref(1)
const showAxes = ref(true)
const showGrid = ref(true)
const autoRotate = ref(false)

const currentModel = ref({
  name: 'Cubo por defecto',
  vertices: [],
  faces: [],
  isDefault: true
})

// Variables para el arrastre
const isDragging = ref(false)
const lastMouse = ref({ x: 0, y: 0 })

// Contexto del canvas
let ctx = null
let animationId = null

// Propiedades computadas
const magnitude = computed(() => {
  const { x, y, z } = rotation.value
  return Math.sqrt(x * x + y * y + z * z)
})

const unitVector = computed(() => {
  const mag = magnitude.value
  if (mag === 0) return '(0, 0, 0)'
  const { x, y, z } = rotation.value
  return `(${(x/mag).toFixed(2)}, ${(y/mag).toFixed(2)}, ${(z/mag).toFixed(2)})`
})

const transformMatrix = computed(() => {
  const { x, y, z } = rotation.value
  const rx = toRadians(x)
  const ry = toRadians(y)
  const rz = toRadians(z)
  
  // Matrices de rotación
  const cos = Math.cos
  const sin = Math.sin
  
  // Matriz combinada de rotación (Z * Y * X)
  return [
    cos(ry) * cos(rz),
    -cos(ry) * sin(rz),
    sin(ry),
    0,
    cos(rx) * sin(rz) + sin(rx) * sin(ry) * cos(rz),
    cos(rx) * cos(rz) - sin(rx) * sin(ry) * sin(rz),
    -sin(rx) * cos(ry),
    0,
    sin(rx) * sin(rz) - cos(rx) * sin(ry) * cos(rz),
    sin(rx) * cos(rz) + cos(rx) * sin(ry) * sin(rz),
    cos(rx) * cos(ry),
    0,
    0, 0, 0, 1
  ]
})

// Funciones utilitarias
const toRadians = (degrees) => degrees * Math.PI / 180

const resetRotation = () => {
  rotation.value = { x: 0, y: 0, z: 0 }
}

const randomRotation = () => {
  rotation.value = {
    x: Math.floor(Math.random() * 360),
    y: Math.floor(Math.random() * 360),
    z: Math.floor(Math.random() * 360)
  }
}

// Funciones de dibujo
const drawGrid = () => {
  if (!showGrid.value) return
  
  ctx.strokeStyle = '#374151'
  ctx.lineWidth = 1
  
  const size = 400
  const step = 20
  
  for (let i = -size; i <= size; i += step) {
    ctx.beginPath()
    ctx.moveTo(i, -size)
    ctx.lineTo(i, size)
    ctx.stroke()
    
    ctx.beginPath()
    ctx.moveTo(-size, i)
    ctx.lineTo(size, i)
    ctx.stroke()
  }
}

const drawAxes = () => {
  if (!showAxes.value) return
  
  const axisLength = 100
  
  // Eje X (Rojo)
  ctx.strokeStyle = '#ef4444'
  ctx.lineWidth = 3
  ctx.beginPath()
  ctx.moveTo(0, 0)
  ctx.lineTo(axisLength, 0)
  ctx.stroke()
  
  // Eje Y (Verde)
  ctx.strokeStyle = '#22c55e'
  ctx.beginPath()
  ctx.moveTo(0, 0)
  ctx.lineTo(0, -axisLength)
  ctx.stroke()
  
  // Eje Z (Azul) - simulado con perspectiva
  ctx.strokeStyle = '#3b82f6'
  ctx.beginPath()
  ctx.moveTo(0, 0)
  ctx.lineTo(-axisLength * 0.7, axisLength * 0.7)
  ctx.stroke()
}

const loadObjFile = async (event) => {
  const file = event.target.files[0]
  if (!file) return
  
  try {
    const text = await file.text()
    const parsed = parseObjFile(text)
    
    currentModel.value = {
      name: file.name,
      vertices: parsed.vertices,
      faces: parsed.faces,
      isDefault: false
    }
    
    // Centrar y escalar el modelo
    normalizeModel()
    
  } catch (error) {
    console.error('Error cargando archivo OBJ:', error)
    alert('Error al cargar el archivo. Asegúrate de que sea un archivo .obj válido.')
  }
}

const parseObjFile = (text) => {
  const vertices = []
  const faces = []
  
  const lines = text.split('\n')
  
  for (const line of lines) {
    const parts = line.trim().split(/\s+/)
    
    if (parts[0] === 'v') {
      // Vértice: v x y z
      const x = parseFloat(parts[1])
      const y = parseFloat(parts[2])
      const z = parseFloat(parts[3])
      vertices.push([x, y, z])
    } else if (parts[0] === 'f') {
      // Cara: f v1 v2 v3 (puede tener más vértices)
      const faceVertices = []
      for (let i = 1; i < parts.length; i++) {
        // Manejar formato v/vt/vn o solo v
        const vertexIndex = parseInt(parts[i].split('/')[0]) - 1 // OBJ usa índices base 1
        faceVertices.push(vertexIndex)
      }
      faces.push(faceVertices)
    }
  }
  
  return { vertices, faces }
}

const normalizeModel = () => {
  if (currentModel.value.vertices.length === 0) return
  
  // Encontrar límites del modelo
  let minX = Infinity, maxX = -Infinity
  let minY = Infinity, maxY = -Infinity
  let minZ = Infinity, maxZ = -Infinity
  
  currentModel.value.vertices.forEach(([x, y, z]) => {
    minX = Math.min(minX, x)
    maxX = Math.max(maxX, x)
    minY = Math.min(minY, y)
    maxY = Math.max(maxY, y)
    minZ = Math.min(minZ, z)
    maxZ = Math.max(maxZ, z)
  })
  
  // Calcular centro y escala
  const centerX = (minX + maxX) / 2
  const centerY = (minY + maxY) / 2
  const centerZ = (minZ + maxZ) / 2
  
  const sizeX = maxX - minX
  const sizeY = maxY - minY
  const sizeZ = maxZ - minZ
  const maxSize = Math.max(sizeX, sizeY, sizeZ)
  
  const targetSize = 120 // Tamaño objetivo
  const scaleFactor = targetSize / maxSize
  
  // Normalizar vértices
  currentModel.value.vertices = currentModel.value.vertices.map(([x, y, z]) => [
    (x - centerX) * scaleFactor,
    (y - centerY) * scaleFactor,
    (z - centerZ) * scaleFactor
  ])
}

const resetToDefaultCube = () => {
  currentModel.value = {
    name: 'Cubo por defecto',
    vertices: [],
    faces: [],
    isDefault: true
  }
}

const drawDefaultCube = () => {
  const size = 60
  const { x, y, z } = rotation.value
  
  // Vértices del cubo
  const vertices = [
    [-size, -size, -size], [size, -size, -size], [size, size, -size], [-size, size, -size],
    [-size, -size, size], [size, -size, size], [size, size, size], [-size, size, size]
  ]
  
  // Aplicar rotaciones
  const rotatedVertices = vertices.map(vertex => applyRotations(vertex))
  
  // Caras del cubo (índices de vértices)
  const faces = [
    [0, 1, 2, 3], [4, 7, 6, 5], [0, 4, 5, 1],
    [2, 6, 7, 3], [0, 3, 7, 4], [1, 5, 6, 2]
  ]
  
  const faceColors = ['#ef4444', '#22c55e', '#3b82f6', '#f59e0b', '#8b5cf6', '#ec4899']
  
  drawFaces(rotatedVertices, faces, faceColors)
}

const drawObjModel = () => {
  if (currentModel.value.vertices.length === 0) return
  
  // Aplicar rotaciones a todos los vértices
  const rotatedVertices = currentModel.value.vertices.map(vertex => applyRotations(vertex))
  
  // Generar colores para las caras
  const faceColors = generateFaceColors(currentModel.value.faces.length)
  
  drawFaces(rotatedVertices, currentModel.value.faces, faceColors)
}

const applyRotations = (vertex) => {
  let [vx, vy, vz] = vertex
  const { x, y, z } = rotation.value
  
  // Rotación X
  const rx = toRadians(x)
  let ny = vy * Math.cos(rx) - vz * Math.sin(rx)
  let nz = vy * Math.sin(rx) + vz * Math.cos(rx)
  vy = ny
  vz = nz
  
  // Rotación Y
  const ry = toRadians(y)
  let nx = vx * Math.cos(ry) + vz * Math.sin(ry)
  nz = -vx * Math.sin(ry) + vz * Math.cos(ry)
  vx = nx
  vz = nz
  
  // Rotación Z
  const rz = toRadians(z)
  nx = vx * Math.cos(rz) - vy * Math.sin(rz)
  ny = vx * Math.sin(rz) + vy * Math.cos(rz)
  vx = nx
  vy = ny
  
  // Proyección 2D con perspectiva
  const distance = 300
  const projectedX = (vx * distance) / (distance + vz)
  const projectedY = (vy * distance) / (distance + vz)
  
  return [projectedX, projectedY, vz]
}

const generateFaceColors = (faceCount) => {
  const colors = []
  for (let i = 0; i < faceCount; i++) {
    const hue = (i * 137.508) % 360 // Distribución áurea para colores diversos
    colors.push(`hsl(${hue}, 70%, 60%)`)
  }
  return colors
}

const drawFaces = (rotatedVertices, faces, faceColors) => {
  // Calcular normales y ordenar por profundidad
  const facesWithDepth = faces.map((face, index) => {
    const avgZ = face.reduce((sum, vertexIndex) => {
      return sum + (rotatedVertices[vertexIndex] ? rotatedVertices[vertexIndex][2] : 0)
    }, 0) / face.length
    
    return { 
      face, 
      color: faceColors[index % faceColors.length], 
      depth: avgZ, 
      index 
    }
  }).filter(f => f.face.every(idx => rotatedVertices[idx])) // Filtrar caras con vértices válidos
  
  facesWithDepth.sort((a, b) => a.depth - b.depth)
  
  // Dibujar caras
  facesWithDepth.forEach(({ face, color }) => {
    if (face.length < 3) return // Necesitamos al menos 3 vértices
    
    ctx.fillStyle = color + '80' // Semi-transparente
    ctx.strokeStyle = color
    ctx.lineWidth = 1
    
    ctx.beginPath()
    face.forEach((vertexIndex, i) => {
      if (!rotatedVertices[vertexIndex]) return
      const [x, y] = rotatedVertices[vertexIndex]
      if (i === 0) {
        ctx.moveTo(x, y)
      } else {
        ctx.lineTo(x, y)
      }
    })
    ctx.closePath()
    ctx.fill()
    ctx.stroke()
  })
  
  // Dibujar vértices
  ctx.fillStyle = '#ffffff'
  rotatedVertices.forEach(([x, y]) => {
    if (x !== undefined && y !== undefined) {
      ctx.beginPath()
      ctx.arc(x, y, 2, 0, 2 * Math.PI)
      ctx.fill()
    }
  })
}

const render = () => {
  if (!ctx) return
  
  // Limpiar canvas
  ctx.clearRect(0, 0, canvas.value.width, canvas.value.height)
  
  // Configurar transformación
  ctx.save()
  ctx.translate(canvas.value.width / 2, canvas.value.height / 2)
  ctx.scale(scale.value, scale.value)
  
  // Dibujar elementos
  drawGrid()
  drawAxes()
  drawCurrentModel()
  
  ctx.restore()
}

const drawCurrentModel = () => {
  if (currentModel.value.isDefault) {
    drawDefaultCube()
  } else {
    drawObjModel()
  }
}

// Eventos de mouse
const startDrag = (e) => {
  isDragging.value = true
  lastMouse.value = { x: e.clientX, y: e.clientY }
}

const drag = (e) => {
  if (!isDragging.value) return
  
  const deltaX = e.clientX - lastMouse.value.x
  const deltaY = e.clientY - lastMouse.value.y
  
  rotation.value.y += deltaX * 0.5
  rotation.value.x += deltaY * 0.5
  
  // Mantener ángulos en rango 0-360
  rotation.value.x = ((rotation.value.x % 360) + 360) % 360
  rotation.value.y = ((rotation.value.y % 360) + 360) % 360
  
  lastMouse.value = { x: e.clientX, y: e.clientY }
}

const endDrag = () => {
  isDragging.value = false
}

const zoom = (e) => {
  e.preventDefault()
  const delta = e.deltaY > 0 ? 0.9 : 1.1
  scale.value = Math.max(0.1, Math.min(3, scale.value * delta))
}

// Animación automática
const animate = () => {
  if (autoRotate.value) {
    rotation.value.y = (rotation.value.y + 1) % 360
  }
  render()
  animationId = requestAnimationFrame(animate)
}

// Watchers
watch([rotation, scale, showAxes, showGrid], render, { deep: true })

// Lifecycle
const resizeCanvas = () => {
  const rect = canvas.value.parentElement.getBoundingClientRect()
  canvas.value.width = rect.width
  canvas.value.height = rect.height
  render()
}

onMounted(() => {
  ctx = canvas.value.getContext('2d')
  
  // Configurar canvas
  resizeCanvas()
  window.addEventListener('resize', resizeCanvas)
  
  // Iniciar animación
  animate()
})

onUnmounted(() => {
  if (animationId) {
    cancelAnimationFrame(animationId)
  }
  window.removeEventListener('resize', resizeCanvas)
})
</script>

<style scoped>
.slider::-webkit-slider-thumb {
  appearance: none;
  height: 20px;
  width: 20px;
  border-radius: 50%;
  background: #3b82f6;
  cursor: pointer;
  border: 2px solid #1e293b;
}

.slider::-moz-range-thumb {
  height: 20px;
  width: 20px;
  border-radius: 50%;
  background: #3b82f6;
  cursor: pointer;
  border: 2px solid #1e293b;
}
</style>
