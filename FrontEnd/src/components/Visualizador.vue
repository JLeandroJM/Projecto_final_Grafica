<template>
  <div class="max-w-7xl mx-auto">
    <div class="text-center mb-8">
      <h1 class="text-4xl font-bold text-white mb-4">Visualizador 3D</h1>
      <p class="text-slate-300">Arrastra tu archivo .obj para visualización instantánea con Three.js</p>
    </div>

    <div class="grid lg:grid-cols-4 gap-6">
      <!-- Panel izquierdo: Estadísticas -->
      <div class="lg:col-span-1">
        <div class="bg-slate-800/50 backdrop-blur-sm rounded-xl p-6 border border-slate-700">
          <h3 class="text-xl font-semibold text-white mb-4 flex items-center">
            <svg class="w-5 h-5 mr-2 text-green-400" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M9 19v-6a2 2 0 00-2-2H5a2 2 0 00-2 2v6a2 2 0 002 2h2a2 2 0 002-2zm0 0V9a2 2 0 012-2h2a2 2 0 012 2v10m-6 0a2 2 0 002 2h2a2 2 0 002-2m0 0V5a2 2 0 012-2h2a2 2 0 012 2v4a2 2 0 01-2 2h-2a2 2 0 00-2 2z"></path>
            </svg>
            Métricas del Modelo
          </h3>
          
          <div v-if="modelLoaded && modelStats" class="space-y-3 text-sm">
            <div class="flex justify-between">
              <span class="text-slate-400">🔷 Vértices:</span>
              <span class="font-mono text-white">{{ modelStats.vertices.toLocaleString() }}</span>
            </div>
            <div class="flex justify-between">
              <span class="text-slate-400">🔺 Caras:</span>
              <span class="font-mono text-white">{{ modelStats.faces.toLocaleString() }}</span>
            </div>
            <div class="flex justify-between">
              <span class="text-slate-400">📐 Aristas:</span>
              <span class="font-mono text-white">{{ modelStats.edges.toLocaleString() }}</span>
            </div>
            <hr class="border-slate-600">
            <div class="text-slate-400 mb-2">📏 Tamaño (bbox):</div>
            <div class="ml-4 space-y-1">
              <div class="flex justify-between">
                <span class="text-slate-500">Ancho:</span>
                <span class="font-mono text-white">{{ modelStats.size.x.toFixed(2) }}</span>
              </div>
              <div class="flex justify-between">
                <span class="text-slate-500">Alto:</span>
                <span class="font-mono text-white">{{ modelStats.size.y.toFixed(2) }}</span>
              </div>
              <div class="flex justify-between">
                <span class="text-slate-500">Profundidad:</span>
                <span class="font-mono text-white">{{ modelStats.size.z.toFixed(2) }}</span>
              </div>
            </div>
          </div>
          
          <div v-else class="text-center py-8">
            <svg class="w-12 h-12 mx-auto mb-4 text-slate-600" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M7 16a4 4 0 01-.88-7.903A5 5 0 1115.9 6L16 6a5 5 0 011 9.9M15 13l-3-3m0 0l-3 3m3-3v12"></path>
            </svg>
            <p class="text-slate-400 text-sm">
              Arrastra un archivo <code class="bg-slate-700 px-2 py-1 rounded text-blue-400">.obj</code> para cargar modelo
            </p>
          </div>
        </div>

        <!-- Controles de visualización -->
        <div class="mt-6 bg-slate-800/50 backdrop-blur-sm rounded-xl p-6 border border-slate-700">
          <h3 class="text-xl font-semibold text-white mb-4 flex items-center">
            <svg class="w-5 h-5 mr-2 text-purple-400" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M15 12a3 3 0 11-6 0 3 3 0 016 0z"></path>
            </svg>
            Controles
          </h3>
          
          <div class="space-y-3">
            <label class="flex items-center text-white">
              <input v-model="showWireframe" type="checkbox" class="mr-2" @change="toggleWireframe" />
              <span class="text-sm">Modo Wireframe</span>
            </label>
            <label class="flex items-center text-white">
              <input v-model="autoRotate" type="checkbox" class="mr-2" @change="toggleAutoRotate" />
              <span class="text-sm">Rotación Automática</span>
            </label>
            <div class="mt-4">
              <button 
                @click="resetCamera"
                class="w-full py-2 px-4 bg-blue-600 hover:bg-blue-500 rounded-lg transition-colors text-white font-medium text-sm"
              >
                Resetear Cámara
              </button>
            </div>
          </div>
        </div>
      </div>

      <!-- Centro: Visor 3D -->
      <div class="lg:col-span-2">
        <div class="bg-slate-800/50 backdrop-blur-sm rounded-xl p-6 border border-slate-700">
          <div 
            ref="container" 
            class="w-full h-96 bg-slate-900 rounded-lg overflow-hidden relative border-2 border-dashed border-slate-600 hover:border-blue-400 transition-colors duration-300"
            @dragover.prevent 
            @drop="onDrop"
          >
            <div v-if="!modelLoaded" class="absolute inset-0 flex items-center justify-center">
              <div class="text-center text-slate-400">
                <svg class="w-16 h-16 mx-auto mb-4 opacity-50" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                  <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M7 16a4 4 0 01-.88-7.903A5 5 0 1115.9 6L16 6a5 5 0 011 9.9M15 13l-3-3m0 0l-3 3m3-3v12"></path>
                </svg>
                <p class="text-lg font-medium">Arrastra tu archivo .obj aquí</p>
                <p class="text-sm mt-2">Visualización optimizada con Three.js</p>
              </div>
            </div>
          </div>
          
          <div v-if="modelLoaded" class="mt-4 text-center">
            <div class="flex justify-center space-x-4 text-sm text-slate-400">
              <span>🖱️ Click y arrastra para rotar</span>
              <span>🔍 Scroll para zoom</span>
              <span>⚡ Renderizado WebGL</span>
            </div>
          </div>
        </div>
      </div>

      <!-- Panel derecho: Información -->
      <div class="lg:col-span-1">
        <div class="bg-slate-800/50 backdrop-blur-sm rounded-xl p-6 border border-slate-700">
          <h3 class="text-xl font-semibold text-white mb-4 flex items-center">
            <svg class="w-5 h-5 mr-2 text-orange-400" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M13 16h-1v-4h-1m1-4h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z"></path>
            </svg>
            Información
          </h3>
          
          <div class="space-y-4 text-sm text-slate-300">
            <p>
              Este visualizador utiliza <strong class="text-blue-400">Three.js</strong> para renderizado WebGL optimizado, 
              permitiendo la visualización fluida de modelos 3D complejos.
            </p>
            
            <div class="bg-slate-700 rounded-lg p-3">
              <h4 class="font-semibold text-white mb-2">Características:</h4>
              <ul class="space-y-1 text-xs">
                <li>• Renderizado acelerado por GPU</li>
                <li>• Controles de órbita suaves</li>
                <li>• Carga optimizada de archivos .obj</li>
                <li>• Cálculo automático de normales</li>
                <li>• Iluminación direccional</li>
                <li>• Modo wireframe</li>
                <li>• Rotación automática</li>
              </ul>
            </div>

            <div v-if="currentFileName" class="bg-blue-900/30 border border-blue-500/30 rounded-lg p-3">
              <h4 class="font-semibold text-blue-400 mb-2 flex items-center">
                <svg class="w-4 h-4 mr-1" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                  <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M9 12h6m-6 4h6m2 5H7a2 2 0 01-2-2V5a2 2 0 012-2h5.586a1 1 0 01.707.293l5.414 5.414a1 1 0 01.293.707V19a2 2 0 01-2 2z"></path>
                </svg>
                Archivo Cargado
              </h4>
              <p class="text-blue-300 text-xs font-mono">{{ currentFileName }}</p>
            </div>

            <div class="text-center">
              <input 
                ref="fileInput"
                type="file" 
                accept=".obj"
                @change="loadFromInput"
                class="hidden"
              />
              <button 
                @click="$refs.fileInput.click()"
                class="w-full py-2 px-4 bg-yellow-600 hover:bg-yellow-500 rounded-lg transition-colors text-white font-medium text-sm flex items-center justify-center"
              >
                <svg class="w-4 h-4 mr-2" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                  <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M7 16a4 4 0 01-.88-7.903A5 5 0 1115.9 6L16 6a5 5 0 011 9.9M15 13l-3-3m0 0l-3 3m3-3v12"></path>
                </svg>
                Seleccionar archivo .obj
              </button>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script setup>
import { ref, onMounted, onUnmounted, nextTick } from 'vue'
import * as THREE from 'three'
import { OBJLoader } from 'three/examples/jsm/loaders/OBJLoader.js'
import { OrbitControls } from 'three/examples/jsm/controls/OrbitControls.js'

const container = ref(null)
const modelLoaded = ref(false)
const modelStats = ref(null)
const currentFileName = ref('')
const showWireframe = ref(false)
const autoRotate = ref(false)

let scene, camera, renderer, objLoader, controls
let currentObject = null
let animationId = null

onMounted(async () => {
  // Esperar a que el DOM esté completamente renderizado
  await nextTick()
  // Pequeño delay adicional para asegurar que el contenedor tenga sus dimensiones
  setTimeout(() => {
    initThreeJS()
  }, 100)
})

onUnmounted(() => {
  if (animationId) {
    cancelAnimationFrame(animationId)
  }
  if (renderer) {
    renderer.dispose()
  }
  window.removeEventListener('resize', onWindowResize)
})

function initThreeJS() {
  if (!container.value) {
    console.error('Container not available')
    return
  }

  const width = container.value.clientWidth
  const height = container.value.clientHeight

  if (width === 0 || height === 0) {
    console.error('Container has no dimensions')
    return
  }

  // Escena
  scene = new THREE.Scene()
  scene.background = new THREE.Color(0x0f172a) // slate-900

  // Cámara
  camera = new THREE.PerspectiveCamera(75, width / height, 0.1, 1000)
  camera.position.set(0, 0, 4)

  // Renderer
  renderer = new THREE.WebGLRenderer({ antialias: true })
  renderer.setSize(width, height)
  renderer.shadowMap.enabled = true
  renderer.shadowMap.type = THREE.PCFSoftShadowMap
  container.value.appendChild(renderer.domElement)

  // Iluminación
  const ambientLight = new THREE.AmbientLight(0x404040, 0.4)
  scene.add(ambientLight)

  const directionalLight = new THREE.DirectionalLight(0xffffff, 0.8)
  directionalLight.position.set(1, 1, 1).normalize()
  directionalLight.castShadow = true
  scene.add(directionalLight)

  // Loader
  objLoader = new OBJLoader()

  // Controles
  controls = new OrbitControls(camera, renderer.domElement)
  controls.enableDamping = true
  controls.dampingFactor = 0.05
  controls.zoomSpeed = 1.2
  controls.minDistance = 0.5
  controls.maxDistance = 50
  controls.autoRotate = false
  controls.autoRotateSpeed = 2.0

  // Iniciar animación
  animate()

  // Manejar redimensionamiento
  window.addEventListener('resize', onWindowResize)

  // Render inicial
  renderer.render(scene, camera)
}

function animate() {
  animationId = requestAnimationFrame(animate)
  
  if (controls) {
    controls.update()
  }
  
  if (renderer && scene && camera) {
    renderer.render(scene, camera)
  }
}

function onWindowResize() {
  if (!container.value || !camera || !renderer) return
  
  const width = container.value.clientWidth
  const height = container.value.clientHeight

  camera.aspect = width / height
  camera.updateProjectionMatrix()
  renderer.setSize(width, height)
  
  // Render inmediato después del resize
  renderer.render(scene, camera)
}

function loadModel(objContent, fileName) {
  try {
    // Parsear el objeto
    const object = objLoader.parse(objContent)
    
    // Limpiar escena de modelos anteriores
    if (currentObject) {
      scene.remove(currentObject)
    }

    // Aplicar material
    const material = new THREE.MeshLambertMaterial({ 
      color: 0x61dafb,
      transparent: false,
      opacity: 1,
      wireframe: showWireframe.value
    })

    object.traverse(child => {
      if (child.isMesh) {
        child.material = material
        child.geometry.computeVertexNormals()
        child.geometry.computeBoundingBox()
        child.castShadow = true
        child.receiveShadow = true
      }
    })

    // Centrar el objeto
    const box = new THREE.Box3().setFromObject(object)
    const center = box.getCenter(new THREE.Vector3())
    object.position.sub(center)

    // Escalar para que quepa en la vista
    const size = box.getSize(new THREE.Vector3())
    const maxDim = Math.max(size.x, size.y, size.z)
    const scale = 3 / maxDim
    object.scale.setScalar(scale)

    scene.add(object)
    currentObject = object

    // Calcular estadísticas
    let totalVertices = 0
    let totalFaces = 0
    const bbox = new THREE.Box3().setFromObject(object)

    object.traverse(child => {
      if (child.isMesh && child.geometry) {
        const position = child.geometry.getAttribute('position')
        if (position) {
          totalVertices += position.count
          totalFaces += position.count / 3
        }
      }
    })

    modelStats.value = {
      vertices: totalVertices,
      faces: Math.round(totalFaces),
      edges: Math.round(totalFaces * 3 / 2),
      size: bbox.getSize(new THREE.Vector3())
    }

    modelLoaded.value = true
    currentFileName.value = fileName

    // Ajustar cámara
    const distance = maxDim * 2
    camera.position.set(distance, distance, distance)
    controls.target.set(0, 0, 0)
    controls.update()

    // IMPORTANTE: Render inmediato para mostrar el objeto
    renderer.render(scene, camera)

  } catch (error) {
    console.error('Error al cargar el modelo:', error)
    alert('Error al cargar el archivo. Asegúrate de que sea un archivo .obj válido.')
  }
}

function onDrop(event) {
  event.preventDefault()
  const file = event.dataTransfer.files[0]
  
  if (!file || !file.name.endsWith('.obj')) {
    alert('Por favor arrastra un archivo .obj válido.')
    return
  }

  const reader = new FileReader()
  reader.onload = e => {
    loadModel(e.target.result, file.name)
  }
  reader.readAsText(file)
}

function loadFromInput(event) {
  const file = event.target.files[0]
  if (!file) return

  const reader = new FileReader()
  reader.onload = e => {
    loadModel(e.target.result, file.name)
  }
  reader.readAsText(file)
}

function toggleWireframe() {
  if (!currentObject) return
  
  currentObject.traverse(child => {
    if (child.isMesh) {
      child.material.wireframe = showWireframe.value
    }
  })
  
  // Render inmediato para mostrar el cambio
  renderer.render(scene, camera)
}

function toggleAutoRotate() {
  if (controls) {
    controls.autoRotate = autoRotate.value
  }
}

function resetCamera() {
  if (!currentObject || !camera || !controls) return
  
  const box = new THREE.Box3().setFromObject(currentObject)
  const size = box.getSize(new THREE.Vector3())
  const maxDim = Math.max(size.x, size.y, size.z)
  const distance = maxDim * 2
  
  camera.position.set(distance, distance, distance)
  controls.target.set(0, 0, 0)
  controls.update()
  
  // Render inmediato para mostrar el cambio
  renderer.render(scene, camera)
}
</script>