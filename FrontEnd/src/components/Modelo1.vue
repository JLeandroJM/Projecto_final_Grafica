<template>
<div class="max-w-7xl mx-auto">
  <div class="text-center mb-8">
    <h1 class="text-4xl font-bold text-white mb-4">QEM Remeshing - Quadric Error Metrics</h1>
    <p class="text-slate-300">Simplificación inteligente de mallas preservando características geométricas críticas</p>
  </div>

  <!-- Panel Superior: Controles -->
  <div class="grid lg:grid-cols-3 gap-6 mb-8">
    <!-- Panel izquierdo: Procesamiento -->
    <div class="lg:col-span-1">
      <div class="bg-slate-800/50 backdrop-blur-sm rounded-xl p-6 border border-slate-700">
        <h3 class="text-xl font-semibold text-white mb-4 flex items-center">
          <svg class="w-5 h-5 mr-2 text-green-400" fill="none" stroke="currentColor" viewBox="0 0 24 24">
            <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M9 19v-6a2 2 0 00-2-2H5a2 2 0 00-2 2v6a2 2 0 002 2h2a2 2 0 002-2zm0 0V9a2 2 0 012-2h2a2 2 0 012 2v10m-6 0a2 2 0 002 2h2a2 2 0 002-2m0 0V5a2 2 0 012-2h2a2 2 0 012 2v4a2 2 0 01-2-2h-2a2 2 0 00-2 2z"></path>
          </svg>
          Estado QEM
        </h3>
        
        <div v-if="originalLoaded" class="space-y-3 text-sm">
          <div class="flex justify-between">
            <span class="text-slate-400">📁 Archivo:</span>
            <span class="font-mono text-white text-xs">{{ currentFileName }}</span>
          </div>
          <div class="flex justify-between">
            <span class="text-slate-400">📊 Estado Original:</span>
            <span class="text-green-400">✓ Cargado</span>
          </div>
          <div class="flex justify-between">
            <span class="text-slate-400">⚙️ Estado QEM:</span>
            <span :class="processedLoaded ? 'text-green-400' : (isProcessing ? 'text-yellow-400' : 'text-slate-400')">
              {{ processedLoaded ? '✓ Simplificado' : (isProcessing ? '⏳ Procesando...' : '⏸️ Listo para procesar') }}
            </span>
          </div>
          <div class="flex justify-between">
            <span class="text-slate-400">🎯 Vértices Objetivo:</span>
            <span class="text-blue-400">{{ targetVertices.toLocaleString() }}</span>
          </div>
          <div v-if="activeTab === 'factor'" class="flex justify-between">
            <span class="text-slate-400">🔧 Factor Reducción:</span>
            <span class="text-purple-400">{{ reductionFactor.toFixed(2) }}</span>
          </div>
        </div>
        
        <div v-else class="text-center py-8">
          <svg class="w-12 h-12 mx-auto mb-4 text-slate-600" fill="none" stroke="currentColor" viewBox="0 0 24 24">
            <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M7 16a4 4 0 01-.88-7.903A5 5 0 1115.9 6L16 6a5 5 0 011 9.9M15 13l-3-3m0 0l-3 3m3-3v12"></path>
          </svg>
          <p class="text-slate-400 text-sm">
            Arrastra un archivo <code class="bg-slate-700 px-2 py-1 rounded text-blue-400">.obj</code> para aplicar QEM
          </p>
        </div>
      </div>
    </div>

    <!-- Control de parámetros con tabs -->
    <div class="lg:col-span-1">
      <div class="bg-slate-800/50 backdrop-blur-sm rounded-xl p-6 border border-slate-700">
        <h3 class="text-xl font-semibold text-white mb-4 flex items-center">
          <svg class="w-5 h-5 mr-2 text-purple-400" fill="none" stroke="currentColor" viewBox="0 0 24 24">
            <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M12 6V4m0 2a2 2 0 100 4m0-4a2 2 0 110 4m-6 8a2 2 0 100-4m0 4a2 2 0 100 4m0-4v2m0-6V4m6 6v10m6-2a2 2 0 100-4m0 4a2 2 0 100 4m0-4v2m0-6V4"></path>
          </svg>
          Parámetros QEM
        </h3>
        
        <!-- Tabs para seleccionar modo -->
        <div class="flex mb-4 bg-slate-700 rounded-lg p-1">
          <button 
            @click="activeTab = 'factor'"
            :class="[
              'flex-1 py-2 px-3 rounded-md text-sm font-medium transition-colors',
              activeTab === 'factor' ? 'bg-purple-600 text-white' : 'text-slate-300 hover:text-white'
            ]"
          >
            Por Factor
          </button>
          <button 
            @click="activeTab = 'vertices'"
            :class="[
              'flex-1 py-2 px-3 rounded-md text-sm font-medium transition-colors',
              activeTab === 'vertices' ? 'bg-purple-600 text-white' : 'text-slate-300 hover:text-white'
            ]"
          >
            Por Vértices
          </button>
        </div>

        <div class="space-y-4">
          <!-- Tab: Factor de Reducción -->
          <div v-if="activeTab === 'factor'">
            <label class="block text-sm font-medium text-gray-300 mb-2">
              Factor de Reducción: {{ reductionFactor.toFixed(2) }}
            </label>
            <input 
              v-model.number="reductionFactor" 
              type="range" 
              min="0.1" 
              max="0.9" 
              step="0.1"
              class="w-full h-2 bg-slate-700 rounded-lg appearance-none cursor-pointer slider"
              :disabled="isProcessing"
            >
            <div class="flex justify-between text-xs text-slate-500 mt-1">
              <span>Máxima reducción</span>
              <span>Mínima reducción</span>
            </div>
            <div class="mt-2 text-center text-sm text-slate-400">
              Resultado: {{ targetVertices.toLocaleString() }} vértices
            </div>
          </div>

          <!-- Tab: Vértices Específicos -->
          <div v-if="activeTab === 'vertices'">
            <label class="block text-sm font-medium text-gray-300 mb-2">
              Número de Vértices Objetivo
            </label>
            <input 
              v-model.number="manualVertices"
              type="number" 
              :min="originalStats ? Math.floor(originalStats.vertices * 0.1) : 100"
              :max="originalStats ? Math.floor(originalStats.vertices * 0.9) : 1000"
              class="w-full px-3 py-2 bg-slate-600 border border-slate-500 rounded-lg text-white text-sm focus:outline-none focus:border-purple-400"
              placeholder="Ej: 5000"
              :disabled="isProcessing"
            >
            <div v-if="originalStats" class="text-xs text-slate-400 mt-1">
              Rango válido: {{ Math.floor(originalStats.vertices * 0.1).toLocaleString() }} - {{ Math.floor(originalStats.vertices * 0.9).toLocaleString() }}
            </div>
            <div class="mt-2 text-center text-sm text-slate-400">
              Factor equivalente: {{ manualVertices && originalStats ? (manualVertices / originalStats.vertices).toFixed(2) : '0.00' }}
            </div>
          </div>

          <!-- Botón de Procesamiento -->
          <div class="bg-slate-700/50 rounded-lg p-3">
            <button 
              @click="processModel"
              :disabled="!originalLoaded || isProcessing || !isValidConfiguration"
              :class="[
                'w-full py-3 px-4 rounded-lg transition-colors text-white font-semibold text-sm flex items-center justify-center',
                !originalLoaded || isProcessing || !isValidConfiguration 
                  ? 'bg-slate-600 cursor-not-allowed' 
                  : 'bg-green-600 hover:bg-green-500'
              ]"
            >
              <svg v-if="!isProcessing" class="w-5 h-5 mr-2" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M14.828 14.828a4 4 0 01-5.656 0M9 10h1m4 0h1m-6 4h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z"></path>
              </svg>
              <svg v-else class="animate-spin w-5 h-5 mr-2" fill="none" viewBox="0 0 24 24">
                <circle class="opacity-25" cx="12" cy="12" r="10" stroke="currentColor" stroke-width="4"></circle>
                <path class="opacity-75" fill="currentColor" d="M4 12a8 8 0 018-8V0C5.373 0 0 5.373 0 12h4zm2 5.291A7.962 7.962 0 014 12H0c0 3.042 1.135 5.824 3 7.938l3-2.647z"></path>
              </svg>
              {{ isProcessing ? 'Procesando QEM...' : 'Procesar con QEM' }}
            </button>
            <div v-if="isProcessing" class="text-center mt-2 text-yellow-400 text-sm">
              ⏱️ Tiempo transcurrido: {{ elapsedTime }}s
            </div>
          </div>

          <!-- Controles adicionales -->
          <div class="space-y-3">
            <!-- Modo Wireframe -->
            <div class="flex items-center justify-between">
              <label class="text-sm font-medium text-gray-300 flex items-center">
                <svg class="w-4 h-4 mr-2" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                  <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M4 5a1 1 0 011-1h14a1 1 0 011 1v2a1 1 0 01-1 1H5a1 1 0 01-1-1V5zM4 13a1 1 0 011-1h6a1 1 0 011 1v6a1 1 0 01-1 1H5a1 1 0 01-1-1v-6zM16 13a1 1 0 011-1h2a1 1 0 011 1v6a1 1 0 01-1 1h-2a1 1 0 01-1-1v-6z"></path>
                </svg>
                Modo Wireframe
              </label>
              <input v-model="wireframeMode" type="checkbox" class="toggle-checkbox" @change="toggleWireframe" />
            </div>

            <!-- Rotación Automática -->
            <div class="flex items-center justify-between">
              <label class="text-sm font-medium text-gray-300 flex items-center">
                <svg class="w-4 h-4 mr-2" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                  <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M4 4v5h.582m15.356 2A8.001 8.001 0 004.582 9m0 0H9m11 11v-5h-.581m0 0a8.003 8.003 0 01-15.357-2m15.357 2H15"></path>
                </svg>
                Rotación Automática
              </label>
              <input v-model="autoRotate" type="checkbox" class="toggle-checkbox" @change="toggleAutoRotate" />
            </div>
          </div>
          
          <div class="grid grid-cols-2 gap-2">
            <button 
              @click="resetCameras"
              class="py-2 px-3 bg-blue-600 hover:bg-blue-500 rounded-lg transition-colors text-white font-medium text-sm"
              :disabled="!originalLoaded"
            >
              Resetear Cámaras
            </button>
            <input 
              ref="fileInput"
              type="file" 
              accept=".obj"
              @change="loadFromInput"
              class="hidden"
            />
            <button 
              @click="$refs.fileInput.click()"
              class="py-2 px-3 bg-yellow-600 hover:bg-yellow-500 rounded-lg transition-colors text-white font-medium text-sm"
              :disabled="isProcessing"
            >
              Cargar Modelo
            </button>
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
          Algoritmo QEM
        </h3>
        
        <div class="space-y-3 text-sm text-slate-300">
          <p>
            <strong class="text-green-400">Quadric Error Metrics</strong> utiliza error cuadrático para determinar qué vértices colapsar preservando la forma original.
          </p>
          
          <div class="bg-slate-700 rounded-lg p-3">
            <h4 class="font-semibold text-white mb-2 text-xs">Proceso QEM:</h4>
            <ul class="space-y-1 text-xs">
              <li>• Calcula error cuadrático para cada vértice</li>
              <li>• Evalúa costo de colapso de aristas</li>
              <li>• Colapsa aristas con menor error</li>
              <li>• Preserva características importantes</li>
            </ul>
          </div>

          <div v-if="mensaje" class="bg-green-900/30 border border-green-500/30 rounded-lg p-2">
            <h4 class="font-semibold text-green-400 mb-1 text-xs">Resultado QEM:</h4>
            <p class="text-green-300 text-xs">{{ mensaje }}</p>
          </div>

          <!-- Cronómetro en tiempo real -->
          <div v-if="isProcessing" class="bg-yellow-900/30 border border-yellow-500/30 rounded-lg p-3">
            <div class="flex items-center justify-center mb-2">
              <svg class="animate-spin w-6 h-6 text-yellow-400 mr-2" fill="none" viewBox="0 0 24 24">
                <circle class="opacity-25" cx="12" cy="12" r="10" stroke="currentColor" stroke-width="4"></circle>
                <path class="opacity-75" fill="currentColor" d="M4 12a8 8 0 018-8V0C5.373 0 0 5.373 0 12h4zm2 5.291A7.962 7.962 0 014 12H0c0 3.042 1.135 5.824 3 7.938l3-2.647z"></path>
              </svg>
              <span class="text-yellow-400 font-semibold text-sm">Procesando QEM...</span>
            </div>
            <div class="text-center">
              <div class="text-yellow-300 text-lg font-mono mb-1">⏱️ {{ elapsedTime }}s</div>
              <div class="text-yellow-300 text-xs">Vértices objetivo: {{ targetVertices.toLocaleString() }}</div>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>

  <!-- Área de Visualización Grande -->
  <div class="grid lg:grid-cols-2 gap-8">
    <!-- Modelo Original -->
    <div class="bg-slate-800/50 backdrop-blur-sm rounded-xl p-6 border border-slate-700">
      <h3 class="text-2xl font-semibold text-white mb-4 text-center flex items-center justify-center">
        <div class="w-4 h-4 bg-blue-400 rounded-full mr-3"></div>
        Malla Original
      </h3>
      
      <div 
        ref="originalContainer" 
        class="w-full h-80 bg-white rounded-lg overflow-hidden relative border-2 border-dashed border-slate-600 hover:border-blue-400 transition-colors duration-300 mb-4"
        @dragover.prevent 
        @drop="onDrop"
      >
        <div v-if="!originalLoaded" class="absolute inset-0 flex items-center justify-center bg-white">
          <div class="text-center text-slate-600">
            <svg class="w-16 h-16 mx-auto mb-4 opacity-50" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M7 16a4 4 0 01-.88-7.903A5 5 0 1115.9 6L16 6a5 5 0 011 9.9M15 13l-3-3m0 0l-3 3m3-3v12"></path>
            </svg>
            <p class="text-lg font-medium">Arrastra archivo .obj aquí</p>
            <p class="text-sm mt-2">Malla de alta resolución</p>
          </div>
        </div>
      </div>

      <!-- Características del Modelo Original -->
      <div v-if="originalLoaded && originalStats" class="bg-slate-700 rounded-lg p-4">
        <h4 class="font-semibold text-blue-400 mb-3 text-center">📊 Malla Original</h4>
        <div class="grid grid-cols-2 gap-4 text-sm">
          <div class="text-center">
            <div class="text-2xl font-bold text-blue-400">{{ originalStats.vertices.toLocaleString() }}</div>
            <div class="text-xs text-slate-400">Vértices</div>
          </div>
          <div class="text-center">
            <div class="text-2xl font-bold text-blue-400">{{ originalStats.faces.toLocaleString() }}</div>
            <div class="text-xs text-slate-400">Caras</div>
          </div>
          <div class="text-center">
            <div class="text-lg font-bold text-blue-400">{{ originalStats.edges.toLocaleString() }}</div>
            <div class="text-xs text-slate-400">Aristas</div>
          </div>
          <div class="text-center">
            <div class="text-lg font-bold text-blue-400">{{ originalStats.volume.toFixed(2) }}</div>
            <div class="text-xs text-slate-400">Volumen</div>
          </div>
        </div>
        
        <div class="mt-3 pt-3 border-t border-slate-600">
          <h5 class="text-slate-300 text-xs mb-2 text-center">Dimensiones (BBox):</h5>
          <div class="grid grid-cols-3 gap-2 text-center">
            <div>
              <div class="text-slate-400 text-xs">Ancho</div>
              <div class="font-mono text-white text-sm">{{ originalStats.size.x.toFixed(2) }}</div>
            </div>
            <div>
              <div class="text-slate-400 text-xs">Alto</div>
              <div class="font-mono text-white text-sm">{{ originalStats.size.y.toFixed(2) }}</div>
            </div>
            <div>
              <div class="text-slate-400 text-xs">Profundidad</div>
              <div class="font-mono text-white text-sm">{{ originalStats.size.z.toFixed(2) }}</div>
            </div>
          </div>
        </div>
      </div>

      <div v-if="originalLoaded" class="mt-3 text-center text-sm text-slate-400">
        🖱️ Click y arrastra • 🔍 Scroll para zoom
      </div>
    </div>

    <!-- Modelo Procesado -->
    <div class="bg-slate-800/50 backdrop-blur-sm rounded-xl p-6 border border-slate-700">
      <h3 class="text-2xl font-semibold text-white mb-4 text-center flex items-center justify-center">
        <div class="w-4 h-4 bg-green-400 rounded-full mr-3"></div>
        Malla Simplificada (QEM)
      </h3>
      
      <div 
        ref="processedContainer" 
        class="w-full h-80 bg-white rounded-lg overflow-hidden relative mb-4"
      >
        <div v-if="!processedLoaded" class="absolute inset-0 flex items-center justify-center bg-white">
          <div class="text-center text-slate-600">
            <svg v-if="isProcessing" class="animate-spin w-12 h-12 mx-auto mb-4" fill="none" viewBox="0 0 24 24">
              <circle class="opacity-25" cx="12" cy="12" r="10" stroke="currentColor" stroke-width="4"></circle>
              <path class="opacity-75" fill="currentColor" d="M4 12a8 8 0 018-8V0C5.373 0 0 5.373 0 12h4zm2 5.291A7.962 7.962 0 014 12H0c0 3.042 1.135 5.824 3 7.938l3-2.647z"></path>
            </svg>
            <svg v-else class="w-12 h-12 mx-auto mb-4 opacity-50" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M12 6V4m0 2a2 2 0 100 4m0-4a2 2 0 110 4m-6 8a2 2 0 100-4m0 4a2 2 0 100 4m0-4v2m0-6V4m6 6v10m6-2a2 2 0 100-4m0 4a2 2 0 100 4m0-4v2m0-6V4"></path>
            </svg>
            <p class="text-lg font-medium text-slate-700">
              {{ isProcessing ? 'Aplicando QEM...' : (originalLoaded ? 'Listo para procesar' : 'Carga un modelo primero') }}
            </p>
            <p v-if="isProcessing" class="text-sm mt-2 text-slate-600">
              Objetivo: {{ targetVertices.toLocaleString() }} vértices
            </p>
            <p v-if="isProcessing" class="text-lg font-mono mt-2 text-yellow-600">
              ⏱️ {{ elapsedTime }}s
            </p>
          </div>
        </div>
      </div>

      <!-- Características del Modelo Procesado -->
      <div v-if="processedLoaded && processedStats" class="bg-slate-700 rounded-lg p-4">
        <h4 class="font-semibold text-green-400 mb-3 text-center">📊 Malla Simplificada</h4>
        <div class="grid grid-cols-2 gap-4 text-sm">
          <div class="text-center">
            <div class="text-2xl font-bold text-green-400">{{ processedStats.vertices.toLocaleString() }}</div>
            <div class="text-xs text-slate-400">Vértices</div>
          </div>
          <div class="text-center">
            <div class="text-2xl font-bold text-green-400">{{ processedStats.faces.toLocaleString() }}</div>
            <div class="text-xs text-slate-400">Caras</div>
          </div>
          <div class="text-center">
            <div class="text-lg font-bold text-green-400">{{ processedStats.edges.toLocaleString() }}</div>
            <div class="text-xs text-slate-400">Aristas</div>
          </div>
          <div class="text-center">
            <div class="text-lg font-bold text-green-400">{{ processedStats.volume.toFixed(2) }}</div>
            <div class="text-xs text-slate-400">Volumen</div>
          </div>
        </div>
        
        <div class="mt-3 pt-3 border-t border-slate-600">
          <h5 class="text-slate-300 text-xs mb-2 text-center">Dimensiones (BBox):</h5>
          <div class="grid grid-cols-3 gap-2 text-center">
            <div>
              <div class="text-slate-400 text-xs">Ancho</div>
              <div class="font-mono text-white text-sm">{{ processedStats.size.x.toFixed(2) }}</div>
            </div>
            <div>
              <div class="text-slate-400 text-xs">Alto</div>
              <div class="font-mono text-white text-sm">{{ processedStats.size.y.toFixed(2) }}</div>
            </div>
            <div>
              <div class="text-slate-400 text-xs">Profundidad</div>
              <div class="font-mono text-white text-sm">{{ processedStats.size.z.toFixed(2) }}</div>
            </div>
          </div>
        </div>

        <!-- Comparación -->
        <div class="mt-3 pt-3 border-t border-slate-600">
          <h5 class="text-purple-400 text-xs mb-2 text-center">📈 Eficiencia QEM:</h5>
          <div class="grid grid-cols-2 gap-2 text-center">
            <div>
              <div class="text-slate-400 text-xs">Reducción Lograda</div>
              <div class="font-mono text-purple-400 text-sm">
                {{ (100 - (processedStats.vertices / originalStats.vertices) * 100).toFixed(1) }}%
              </div>
            </div>
            <div>
              <div class="text-slate-400 text-xs">Tiempo Procesamiento</div>
              <div class="font-mono text-purple-400 text-sm">{{ finalProcessingTime }}s</div>
            </div>
          </div>
        </div>

        <div class="mt-3 pt-3 border-t border-slate-600">
          <button 
            @click="downloadProcessedModel"
            class="w-full py-2 px-4 bg-green-600 hover:bg-green-500 rounded-lg transition-colors text-white font-medium text-sm flex items-center justify-center"
          >
            <svg class="w-4 h-4 mr-2" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M12 10v6m0 0l-4-4m4 4l4-4m-4-4V3"></path>
            </svg>
            Descargar Modelo QEM
          </button>
        </div>
      </div>

      <div v-if="processedLoaded" class="mt-3 text-center text-sm text-slate-400">
        🖱️ Click y arrastra • 🔍 Scroll para zoom
      </div>
    </div>
  </div>
</div>
</template>

<script setup>
import { ref, onMounted, onUnmounted, nextTick, computed, watch } from 'vue'
import * as THREE from 'three'
import { OBJLoader } from 'three/examples/jsm/loaders/OBJLoader.js'
import { OrbitControls } from 'three/examples/jsm/controls/OrbitControls.js'

// Referencias a contenedores
const originalContainer = ref(null)
const processedContainer = ref(null)

// Estados
const originalLoaded = ref(false)
const processedLoaded = ref(false)
const originalStats = ref(null)
const processedStats = ref(null)
const currentFileName = ref('')
const isProcessing = ref(false)
const mensaje = ref('')

// Control de tabs y parámetros
const activeTab = ref('factor')
const reductionFactor = ref(0.5)
const manualVertices = ref(null)

// Cronómetro en tiempo real
const elapsedTime = ref(0)
const finalProcessingTime = ref(0)
let processingTimer = null

// Controles
const wireframeMode = ref(false)
const autoRotate = ref(false)

// Contenido OBJ
let originalObjContent = ''
const processedObjContent = ref('')

// Variables Three.js
let originalScene, originalCamera, originalRenderer, originalControls, originalLoader
let processedScene, processedCamera, processedRenderer, processedControls, processedLoader
let originalAnimationId = null
let processedAnimationId = null

// Computed properties
const targetVertices = computed(() => {
  if (!originalStats.value) return 0
  
  if (activeTab.value === 'factor') {
    return Math.floor(originalStats.value.vertices * reductionFactor.value)
  } else {
    return manualVertices.value || Math.floor(originalStats.value.vertices * reductionFactor.value)
  }
})

const isValidConfiguration = computed(() => {
  if (!originalStats.value) return false
  
  if (activeTab.value === 'factor') {
    return reductionFactor.value >= 0.1 && reductionFactor.value <= 0.9
  } else {
    const min = Math.floor(originalStats.value.vertices * 0.1)
    const max = Math.floor(originalStats.value.vertices * 0.9)
    return manualVertices.value && manualVertices.value >= min && manualVertices.value <= max
  }
})

// Watch para sincronizar tabs
watch(activeTab, (newTab) => {
  if (newTab === 'vertices' && originalStats.value && !manualVertices.value) {
    manualVertices.value = Math.floor(originalStats.value.vertices * reductionFactor.value)
  }
})

watch(manualVertices, (newValue) => {
  if (activeTab.value === 'vertices' && originalStats.value && newValue) {
    const newFactor = newValue / originalStats.value.vertices
    if (newFactor >= 0.1 && newFactor <= 0.9) {
      reductionFactor.value = newFactor
    }
  }
})

// Funciones del cronómetro
function startTimer() {
  elapsedTime.value = 0
  processingTimer = setInterval(() => {
    elapsedTime.value++
  }, 1000)
}

function stopTimer() {
  if (processingTimer) {
    clearInterval(processingTimer)
    processingTimer = null
    finalProcessingTime.value = elapsedTime.value
  }
}

function downloadProcessedModel() {
  if (!processedObjContent.value || !currentFileName.value) {
    alert('No hay modelo procesado para descargar')
    return
  }
  
  const blob = new Blob([processedObjContent.value], { type: 'text/plain' })
  const url = URL.createObjectURL(blob)
  const link = document.createElement('a')
  link.href = url
  link.download = `QEM_${currentFileName.value}`
  document.body.appendChild(link)
  link.click()
  document.body.removeChild(link)
  URL.revokeObjectURL(url)
}

onMounted(async () => {
  await nextTick()
  setTimeout(() => {
    initOriginalViewer()
    initProcessedViewer()
  }, 100)
})

onUnmounted(() => {
  if (originalAnimationId) cancelAnimationFrame(originalAnimationId)
  if (processedAnimationId) cancelAnimationFrame(processedAnimationId)
  if (processingTimer) clearInterval(processingTimer)
  if (originalRenderer) originalRenderer.dispose()
  if (processedRenderer) processedRenderer.dispose()
})

function clearAllStates() {
  originalLoaded.value = false
  processedLoaded.value = false
  originalStats.value = null
  processedStats.value = null
  currentFileName.value = ''
  mensaje.value = ''
  isProcessing.value = false
  manualVertices.value = null
  elapsedTime.value = 0
  finalProcessingTime.value = 0
  
  if (processingTimer) {
    clearInterval(processingTimer)
    processingTimer = null
  }
  
  if (originalScene) {
    while(originalScene.children.length > 0) {
      originalScene.remove(originalScene.children[0])
    }
    const ambientLight = new THREE.AmbientLight(0x404040, 0.6)
    originalScene.add(ambientLight)
    const directionalLight = new THREE.DirectionalLight(0xffffff, 0.8)
    directionalLight.position.set(1, 1, 1).normalize()
    directionalLight.castShadow = true
    originalScene.add(directionalLight)
  }
  
  if (processedScene) {
    while(processedScene.children.length > 0) {
      processedScene.remove(processedScene.children[0])
    }
    const ambientLight = new THREE.AmbientLight(0x404040, 0.6)
    processedScene.add(ambientLight)
    const directionalLight = new THREE.DirectionalLight(0xffffff, 0.8)
    directionalLight.position.set(1, 1, 1).normalize()
    directionalLight.castShadow = true
    processedScene.add(directionalLight)
  }
}

function initOriginalViewer() {
  if (!originalContainer.value) return
  
  const width = originalContainer.value.clientWidth
  const height = originalContainer.value.clientHeight

  originalScene = new THREE.Scene()
  originalScene.background = new THREE.Color(0xffffff)

  originalCamera = new THREE.PerspectiveCamera(75, width / height, 0.1, 1000)
  originalCamera.position.set(0, 0, 4)

  originalRenderer = new THREE.WebGLRenderer({ antialias: true })
  originalRenderer.setSize(width, height)
  originalRenderer.shadowMap.enabled = true
  originalRenderer.shadowMap.type = THREE.PCFSoftShadowMap
  originalContainer.value.appendChild(originalRenderer.domElement)

  const ambientLight = new THREE.AmbientLight(0x404040, 0.6)
  originalScene.add(ambientLight)

  const directionalLight = new THREE.DirectionalLight(0xffffff, 0.8)
  directionalLight.position.set(1, 1, 1).normalize()
  directionalLight.castShadow = true
  originalScene.add(directionalLight)

  originalLoader = new OBJLoader()

  originalControls = new OrbitControls(originalCamera, originalRenderer.domElement)
  originalControls.enableDamping = true
  originalControls.dampingFactor = 0.05
  originalControls.autoRotate = false
  originalControls.autoRotateSpeed = 2.0

  function animateOriginal() {
    originalAnimationId = requestAnimationFrame(animateOriginal)
    if (originalControls) originalControls.update()
    if (originalRenderer && originalScene && originalCamera) {
      originalRenderer.render(originalScene, originalCamera)
    }
  }
  animateOriginal()
}

function initProcessedViewer() {
  if (!processedContainer.value) return
  
  const width = processedContainer.value.clientWidth
  const height = processedContainer.value.clientHeight

  processedScene = new THREE.Scene()
  processedScene.background = new THREE.Color(0xffffff)

  processedCamera = new THREE.PerspectiveCamera(75, width / height, 0.1, 1000)
  processedCamera.position.set(0, 0, 4)

  processedRenderer = new THREE.WebGLRenderer({ antialias: true })
  processedRenderer.setSize(width, height)
  processedRenderer.shadowMap.enabled = true
  processedRenderer.shadowMap.type = THREE.PCFSoftShadowMap
  processedContainer.value.appendChild(processedRenderer.domElement)

  const ambientLight = new THREE.AmbientLight(0x404040, 0.6)
  processedScene.add(ambientLight)

  const directionalLight = new THREE.DirectionalLight(0xffffff, 0.8)
  directionalLight.position.set(1, 1, 1).normalize()
  directionalLight.castShadow = true
  processedScene.add(directionalLight)

  processedLoader = new OBJLoader()

  processedControls = new OrbitControls(processedCamera, processedRenderer.domElement)
  processedControls.enableDamping = true
  processedControls.dampingFactor = 0.05
  processedControls.autoRotate = false
  processedControls.autoRotateSpeed = 2.0

  function animateProcessed() {
    processedAnimationId = requestAnimationFrame(animateProcessed)
    if (processedControls) processedControls.update()
    if (processedRenderer && processedScene && processedCamera) {
      processedRenderer.render(processedScene, processedCamera)
    }
  }
  animateProcessed()
}

function loadOriginalModel(objContent, fileName) {
  const object = originalLoader.parse(objContent)
  
  while(originalScene.children.length > 0) {
    originalScene.remove(originalScene.children[0])
  }
  
  // Limpiar completamente el contenedor y renderizar fondo blanco
  if (originalRenderer && originalCamera) {
    originalRenderer.render(originalScene, originalCamera)
  }
  
  const ambientLight = new THREE.AmbientLight(0x404040, 0.6)
  originalScene.add(ambientLight)
  
  const directionalLight = new THREE.DirectionalLight(0xffffff, 0.8)
  directionalLight.position.set(1, 1, 1).normalize()
  directionalLight.castShadow = true
  originalScene.add(directionalLight)

  const originalMaterial = new THREE.MeshLambertMaterial({ 
    color: 0x61dafb,
    wireframe: wireframeMode.value,
    transparent: false,
    opacity: 1.0,
    side: THREE.DoubleSide
  })

  object.traverse(child => {
    if (child.isMesh) {
      child.material = originalMaterial
      child.geometry.computeVertexNormals()
      child.geometry.computeBoundingBox()
      child.castShadow = true
      child.receiveShadow = true
    }
  })

  const box = new THREE.Box3().setFromObject(object)
  const objectCenter = box.getCenter(new THREE.Vector3())
  object.position.sub(objectCenter)

  const objectSize = box.getSize(new THREE.Vector3())
  const objectMaxDim = Math.max(objectSize.x, objectSize.y, objectSize.z)
  const objectScale = 2 / objectMaxDim
  object.scale.setScalar(objectScale)

  originalScene.add(object)
  originalLoaded.value = true
  currentFileName.value = fileName

  const lines = objContent.split('\n')
  let objVertices = 0
  let objFaces = 0

  for (const line of lines) {
    const trimmed = line.trim()
    if (trimmed.startsWith('v ')) {
      objVertices++
    } else if (trimmed.startsWith('f ')) {
      objFaces++
    }
  }

  originalStats.value = {
    vertices: objVertices,
    faces: objFaces,
    edges: Math.round(objFaces * 3 / 2),
    volume: objectSize.x * objectSize.y * objectSize.z,
    size: objectSize
  }

  const boundingBox = new THREE.Box3().setFromObject(object)
  const center = boundingBox.getCenter(new THREE.Vector3())
  const size = boundingBox.getSize(new THREE.Vector3())

  const maxDim = Math.max(size.x, size.y, size.z)
  const fov = originalCamera.fov * (Math.PI / 180)
  const distance = Math.abs(maxDim / Math.sin(fov / 2)) * 1.2

  originalCamera.position.set(0, 0, distance)
  originalCamera.lookAt(center)

  originalControls.target.copy(center)
  originalControls.minDistance = distance * 0.5
  originalControls.maxDistance = distance * 3
  originalControls.update()
  
  originalRenderer.render(originalScene, originalCamera)
}

async function processModel() {
  if (!originalObjContent || !currentFileName.value || !isValidConfiguration.value) {
    return
  }

  isProcessing.value = true
  processedLoaded.value = false
  mensaje.value = 'Iniciando procesamiento QEM...'
  
  // Iniciar cronómetro
  startTimer()

  try {
    const res = await fetch('http://localhost:3001/api/print', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ 
        obj: originalObjContent, 
        targetVertices: targetVertices.value
      })
    })
    
    if (!res.ok) {
      throw new Error(`HTTP error! status: ${res.status}`)
    }
    
    const data = await res.json()
    processedObjContent.value = data.obj
    mensaje.value = data.mensaje || 'Simplificación QEM completada exitosamente'

    const processedObject = processedLoader.parse(data.obj)
    
    while(processedScene.children.length > 0) {
      processedScene.remove(processedScene.children[0])
    }
    
    const ambientLight = new THREE.AmbientLight(0x404040, 0.6)
    processedScene.add(ambientLight)
    
    const directionalLight = new THREE.DirectionalLight(0xffffff, 0.8)
    directionalLight.position.set(1, 1, 1).normalize()
    directionalLight.castShadow = true
    processedScene.add(directionalLight)

    const processedMaterial = new THREE.MeshLambertMaterial({ 
      color: 0x22c55e,
      wireframe: wireframeMode.value,
      transparent: false,
      opacity: 1.0,
      side: THREE.DoubleSide
    })

    processedObject.traverse(child => {
      if (child.isMesh) {
        child.material = processedMaterial
        child.geometry.computeVertexNormals()
        child.geometry.computeBoundingBox()
        child.castShadow = true
        child.receiveShadow = true
      }
    })

    const box = new THREE.Box3().setFromObject(processedObject)
    const objectCenter = box.getCenter(new THREE.Vector3())
    processedObject.position.sub(objectCenter)

    const objectSize = box.getSize(new THREE.Vector3())
    const objectMaxDim = Math.max(objectSize.x, objectSize.y, objectSize.z)
    const objectScale = 2 / objectMaxDim
    processedObject.scale.setScalar(objectScale)

    processedScene.add(processedObject)
    processedLoaded.value = true

    const processedLines = data.obj.split('\n')
    let processedObjVertices = 0
    let processedObjFaces = 0

    for (const line of processedLines) {
      const trimmed = line.trim()
      if (trimmed.startsWith('v ')) {
        processedObjVertices++
      } else if (trimmed.startsWith('f ')) {
        processedObjFaces++
      }
    }

    processedStats.value = {
      vertices: processedObjVertices,
      faces: processedObjFaces,
      edges: Math.round(processedObjFaces * 3 / 2),
      volume: objectSize.x * objectSize.y * objectSize.z,
      size: objectSize
    }

    const boundingBox = new THREE.Box3().setFromObject(processedObject)
    const center = boundingBox.getCenter(new THREE.Vector3())
    const size = boundingBox.getSize(new THREE.Vector3())

    const maxDim = Math.max(size.x, size.y, size.z)
    const fov = processedCamera.fov * (Math.PI / 180)
    const distance = Math.abs(maxDim / Math.sin(fov / 2)) * 1.2

    processedCamera.position.set(0, 0, distance)
    processedCamera.lookAt(center)

    processedControls.target.copy(center)
    processedControls.minDistance = distance * 0.5
    processedControls.maxDistance = distance * 3
    processedControls.update()
    
    processedRenderer.render(processedScene, processedCamera)

  } catch (error) {
    console.error('Error procesando modelo:', error)
    mensaje.value = 'Error al conectar con la API. Asegúrate de que el servidor esté ejecutándose en http://localhost:3001'
  } finally {
    isProcessing.value = false
    stopTimer()
  }
}

async function onDrop(event) {
  event.preventDefault()
  const file = event.dataTransfer.files[0]
  
  if (!file || !file.name.endsWith('.obj')) {
    alert('Por favor arrastra un archivo .obj válido.')
    return
  }

  clearAllStates()
  
  // Asegurar que el fondo esté limpio durante la carga
  if (originalRenderer && originalScene && originalCamera) {
    originalRenderer.render(originalScene, originalCamera)
  }
  if (processedRenderer && processedScene && processedCamera) {
    processedRenderer.render(processedScene, processedCamera)
  }

  const reader = new FileReader()
  reader.onload = async e => {
    const contents = e.target.result
    originalObjContent = contents
    loadOriginalModel(contents, file.name)
  }
  reader.readAsText(file)
}

function loadFromInput(event) {
  const file = event.target.files[0]
  if (!file) return

  clearAllStates()
  
  // Asegurar que el fondo esté limpio durante la carga
  if (originalRenderer && originalScene && originalCamera) {
    originalRenderer.render(originalScene, originalCamera)
  }
  if (processedRenderer && processedScene && processedCamera) {
    processedRenderer.render(processedScene, processedCamera)
  }

  const reader = new FileReader()
  reader.onload = async e => {
    const contents = e.target.result
    originalObjContent = contents
    loadOriginalModel(contents, file.name)
  }
  reader.readAsText(file)
}

function resetCameras() {
  if (originalLoaded.value && originalScene.children.length > 0) {
    const meshObject = originalScene.children.find(child => child.type === 'Group' || child.type === 'Mesh')
    if (meshObject) {
      const boundingBox = new THREE.Box3().setFromObject(meshObject)
      const center = boundingBox.getCenter(new THREE.Vector3())
      const size = boundingBox.getSize(new THREE.Vector3())
      const maxDim = Math.max(size.x, size.y, size.z)
      const fov = originalCamera.fov * (Math.PI / 180)
      const distance = Math.abs(maxDim / Math.sin(fov / 2)) * 1.2
      
      originalCamera.position.set(0, 0, distance)
      originalCamera.lookAt(center)
      originalControls.target.copy(center)
      originalControls.update()
      originalRenderer.render(originalScene, originalCamera)
    }
  }
  
  if (processedLoaded.value && processedScene.children.length > 0) {
    const meshObject = processedScene.children.find(child => child.type === 'Group' || child.type === 'Mesh')
    if (meshObject) {
      const boundingBox = new THREE.Box3().setFromObject(meshObject)
      const center = boundingBox.getCenter(new THREE.Vector3())
      const size = boundingBox.getSize(new THREE.Vector3())
      const maxDim = Math.max(size.x, size.y, size.z)
      const fov = processedCamera.fov * (Math.PI / 180)
      const distance = Math.abs(maxDim / Math.sin(fov / 2)) * 1.2
      
      processedCamera.position.set(0, 0, distance)
      processedCamera.lookAt(center)
      processedControls.target.copy(center)
      processedControls.update()
      processedRenderer.render(processedScene, processedCamera)
    }
  }
}

function toggleWireframe() {
  if (originalScene) {
    originalScene.traverse(child => {
      if (child.isMesh && child.material) {
        child.material.wireframe = wireframeMode.value
      }
    })
    originalRenderer.render(originalScene, originalCamera)
  }
  
  if (processedScene) {
    processedScene.traverse(child => {
      if (child.isMesh && child.material) {
        child.material.wireframe = wireframeMode.value
      }
    })
    processedRenderer.render(processedScene, processedCamera)
  }
}

function toggleAutoRotate() {
  if (originalControls) {
    originalControls.autoRotate = autoRotate.value
  }
  if (processedControls) {
    processedControls.autoRotate = autoRotate.value
  }
}
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

.toggle-checkbox {
  appearance: none;
  width: 40px;
  height: 20px;
  background-color: #374151;
  border-radius: 10px;
  position: relative;
  cursor: pointer;
  transition: background-color 0.3s;
}

.toggle-checkbox:checked {
  background-color: #3b82f6;
}

.toggle-checkbox::before {
  content: '';
  position: absolute;
  width: 16px;
  height: 16px;
  border-radius: 50%;
  background-color: white;
  top: 2px;
  left: 2px;
  transition: transform 0.3s;
}

.toggle-checkbox:checked::before {
  transform: translateX(20px);
}
</style>
