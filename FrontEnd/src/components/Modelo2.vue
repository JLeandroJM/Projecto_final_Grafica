<template>
<div class="max-w-7xl mx-auto">
  <div class="text-center mb-8">
    <h1 class="text-4xl font-bold text-white mb-4">Remeshing Avanzado con Diagramas de Voronoi</h1>
    <p class="text-slate-300">Selecciona entre 4 algoritmos especializados para optimización de mallas triangulares</p>
  </div>

  <!-- Panel Superior: Selección de Algoritmo -->
  <div class="mb-8">
    <h3 class="text-2xl font-semibold text-white mb-6 text-center">🔬 Selecciona el Algoritmo de Remeshing</h3>
    <div class="grid lg:grid-cols-4 gap-4">
      <!-- Algoritmo 0: Malla Homogénea -->
      <div 
        @click="selectAlgorithm(0)"
        :class="[
          'bg-slate-800/50 backdrop-blur-sm rounded-xl p-4 border-2 cursor-pointer transition-all duration-300 hover:scale-105',
          selectedAlgorithm === 0 ? 'border-blue-400 bg-blue-900/20' : 'border-slate-700 hover:border-blue-300'
        ]"
      >
        <div class="text-center">
          <div class="w-12 h-12 mx-auto mb-3 bg-blue-500 rounded-full flex items-center justify-center">
            <svg class="w-6 h-6 text-white" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M4 6h16M4 12h16M4 18h16"></path>
            </svg>
          </div>
          <h4 class="text-lg font-semibold text-white mb-2">Malla Homogénea</h4>
          <p class="text-sm text-slate-300 mb-3">Densidad constante y uniforme en toda la superficie</p>
          <div class="text-xs text-blue-400 font-medium">Ideal para: Modelos simples</div>
        </div>
      </div>

      <!-- Algoritmo 1: Malla Sensible a Curvatura -->
      <div 
        @click="selectAlgorithm(1)"
        :class="[
          'bg-slate-800/50 backdrop-blur-sm rounded-xl p-4 border-2 cursor-pointer transition-all duration-300 hover:scale-105',
          selectedAlgorithm === 1 ? 'border-green-400 bg-green-900/20' : 'border-slate-700 hover:border-green-300'
        ]"
      >
        <div class="text-center">
          <div class="w-12 h-12 mx-auto mb-3 bg-green-500 rounded-full flex items-center justify-center">
            <svg class="w-6 h-6 text-white" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M13 10V3L4 14h7v7l9-11h-7z"></path>
            </svg>
          </div>
          <h4 class="text-lg font-semibold text-white mb-2">Malla Sensible a Curvatura</h4>
          <p class="text-sm text-slate-300 mb-3">Ajusta la densidad de triángulos según la curvatura local</p>
          <div class="text-xs text-green-400 font-medium">Ideal para: Geometría compleja</div>
        </div>
      </div>

      <!-- Algoritmo 2: Malla Tensorial -->
      <div 
        @click="selectAlgorithm(2)"
        :class="[
          'bg-slate-800/50 backdrop-blur-sm rounded-xl p-4 border-2 cursor-pointer transition-all duration-300 hover:scale-105',
          selectedAlgorithm === 2 ? 'border-purple-400 bg-purple-900/20' : 'border-slate-700 hover:border-purple-300'
        ]"
      >
        <div class="text-center">
          <div class="w-12 h-12 mx-auto mb-3 bg-purple-500 rounded-full flex items-center justify-center">
            <svg class="w-6 h-6 text-white" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M7 16V4m0 0L3 8m4-4l4 4m6 0v12m0 0l4-4m-4 4l-4-4"></path>
            </svg>
          </div>
          <h4 class="text-lg font-semibold text-white mb-2">Malla Tensorial</h4>
          <p class="text-sm text-slate-300 mb-3">Emplea tensores métricos para refinar en direcciones preferentes</p>
          <div class="text-xs text-purple-400 font-medium">Ideal para: Superficies fluidas</div>
        </div>
      </div>

      <!-- Algoritmo 3: Malla Cuádrica-Tensorial -->
      <div 
        @click="selectAlgorithm(3)"
        :class="[
          'bg-slate-800/50 backdrop-blur-sm rounded-xl p-4 border-2 cursor-pointer transition-all duration-300 hover:scale-105',
          selectedAlgorithm === 3 ? 'border-orange-400 bg-orange-900/20' : 'border-slate-700 hover:border-orange-300'
        ]"
      >
        <div class="text-center">
          <div class="w-12 h-12 mx-auto mb-3 bg-orange-500 rounded-full flex items-center justify-center">
            <svg class="w-6 h-6 text-white" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M9.663 17h4.673M12 3v1m6.364 1.636l-.707.707M21 12h-1M4 12H3m3.343-5.657l-.707-.707m2.828 9.9a5 5 0 117.072 0l-.548.547A3.374 3.374 0 0014 18.469V19a2 2 0 11-4 0v-.531c0-.895-.356-1.754-.988-2.386l-.548-.547z"></path>
            </svg>
          </div>
          <h4 class="text-lg font-semibold text-white mb-2">Malla Cuádrica-Tensorial</h4>
          <p class="text-sm text-slate-300 mb-3">Combina métricas anisotrópicas con criterios de error cuádricos</p>
          <div class="text-xs text-orange-400 font-medium">Ideal para: Máxima precisión</div>
        </div>
      </div>
    </div>

    <!-- Descripción detallada del algoritmo seleccionado -->
    <div class="mt-6 bg-slate-800/50 backdrop-blur-sm rounded-xl p-6 border border-slate-700">
      <div v-if="selectedAlgorithm === 0" class="text-center">
        <h4 class="text-xl font-semibold text-blue-400 mb-3">🔵 Malla Homogénea</h4>
        <p class="text-slate-300 mb-4">
          Distribuye los vértices de manera homogénea por toda la superficie, creando una malla regular y equilibrada. 
          Perfecto para modelos con geometría simple donde se requiere una densidad constante de triángulos.
        </p>
        <div class="grid grid-cols-2 gap-4 text-sm">
          <div class="bg-blue-900/20 rounded-lg p-3">
            <div class="text-blue-400 font-semibold mb-1">✅ Ventajas</div>
            <ul class="text-slate-300 space-y-1">
              <li>• Distribución predecible</li>
              <li>• Procesamiento rápido</li>
              <li>• Malla regular</li>
            </ul>
          </div>
          <div class="bg-slate-700/50 rounded-lg p-3">
            <div class="text-slate-400 font-semibold mb-1">⚠️ Limitaciones</div>
            <ul class="text-slate-300 space-y-1">
              <li>• No se adapta a curvaturas</li>
              <li>• Puede sobre-muestrear áreas planas</li>
              <li>• Sub-muestrear áreas complejas</li>
            </ul>
          </div>
        </div>
      </div>

      <div v-if="selectedAlgorithm === 1" class="text-center">
        <h4 class="text-xl font-semibold text-green-400 mb-3">🟢 Malla Sensible a Curvatura</h4>
        <p class="text-slate-300 mb-4">
          Se adapta inteligentemente a las características locales de la superficie, colocando más vértices en áreas de alta curvatura 
          y menos en regiones planas. Ideal para geometrías complejas con variaciones significativas.
        </p>
        <div class="grid grid-cols-2 gap-4 text-sm">
          <div class="bg-green-900/20 rounded-lg p-3">
            <div class="text-green-400 font-semibold mb-1">✅ Ventajas</div>
            <ul class="text-slate-300 space-y-1">
              <li>• Preserva detalles importantes</li>
              <li>• Optimiza densidad de malla</li>
              <li>• Reduce vértices innecesarios</li>
            </ul>
          </div>
          <div class="bg-slate-700/50 rounded-lg p-3">
            <div class="text-slate-400 font-semibold mb-1">⚠️ Consideraciones</div>
            <ul class="text-slate-300 space-y-1">
              <li>• Mayor tiempo de procesamiento</li>
              <li>• Requiere análisis de curvatura</li>
              <li>• Malla menos predecible</li>
            </ul>
          </div>
        </div>
      </div>

      <div v-if="selectedAlgorithm === 2" class="text-center">
        <h4 class="text-xl font-semibold text-purple-400 mb-3">🟣 Malla Tensorial</h4>
        <p class="text-slate-300 mb-4">
          Orienta los triángulos siguiendo las direcciones principales de la superficie, creando elementos alargados 
          que siguen el flujo natural de la geometría. Excelente para superficies con direcciones preferenciales.
        </p>
        <div class="grid grid-cols-2 gap-4 text-sm">
          <div class="bg-purple-900/20 rounded-lg p-3">
            <div class="text-purple-400 font-semibold mb-1">✅ Ventajas</div>
            <ul class="text-slate-300 space-y-1">
              <li>• Sigue direcciones naturales</li>
              <li>• Mejor para simulaciones CFD</li>
              <li>• Elementos más eficientes</li>
            </ul>
          </div>
          <div class="bg-slate-700/50 rounded-lg p-3">
            <div class="text-slate-400 font-semibold mb-1">⚠️ Consideraciones</div>
            <ul class="text-slate-300 space-y-1">
              <li>• Requiere análisis direccional</li>
              <li>• Más complejo de implementar</li>
              <li>• Sensible a parámetros</li>
            </ul>
          </div>
        </div>
      </div>

      <div v-if="selectedAlgorithm === 3" class="text-center">
        <h4 class="text-xl font-semibold text-orange-400 mb-3">🟠 Malla Cuádrica-Tensorial</h4>
        <p class="text-slate-300 mb-4">
          Combina la orientación anisotrópica con métricas cuadráticas para lograr la máxima precisión. 
          Utiliza tensores de curvatura para optimizar tanto la orientación como el tamaño de los elementos.
        </p>
        <div class="grid grid-cols-2 gap-4 text-sm">
          <div class="bg-orange-900/20 rounded-lg p-3">
            <div class="text-orange-400 font-semibold mb-1">✅ Ventajas</div>
            <ul class="text-slate-300 space-y-1">
              <li>• Máxima precisión geométrica</li>
              <li>• Optimización dual</li>
              <li>• Mejor calidad de elementos</li>
            </ul>
          </div>
          <div class="bg-slate-700/50 rounded-lg p-3">
            <div class="text-slate-400 font-semibold mb-1">⚠️ Consideraciones</div>
            <ul class="text-slate-300 space-y-1">
              <li>• Mayor costo computacional</li>
              <li>• Requiere más memoria</li>
              <li>• Configuración más compleja</li>
            </ul>
          </div>
        </div>
      </div>
    </div>
  </div>

  <!-- Panel Superior: Controles -->
  <div class="grid lg:grid-cols-3 gap-6 mb-8">
    <!-- Panel izquierdo: Procesamiento -->
    <div class="lg:col-span-1">
      <div class="bg-slate-800/50 backdrop-blur-sm rounded-xl p-6 border border-slate-700">
        <h3 class="text-xl font-semibold text-white mb-4 flex items-center">
          <svg class="w-5 h-5 mr-2 text-purple-400" fill="none" stroke="currentColor" viewBox="0 0 24 24">
            <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M19 11H5m14 0a2 2 0 012 2v6a2 2 0 01-2 2H5a2 2 0 01-2-2v-6a2 2 0 012-2m14 0V9a2 2 0 00-2-2M5 11V9a2 2 0 012-2m0 0V5a2 2 0 012-2h6a2 2 0 012 2v2M7 7h10"></path>
          </svg>
          Estado Procesamiento
        </h3>
        
        <div v-if="originalModel.vertices.length > 0" class="space-y-3 text-sm">
          <div class="flex justify-between">
            <span class="text-slate-400">📁 Archivo:</span>
            <span class="font-mono text-white text-xs">{{ originalModel.name }}</span>
          </div>
          <div class="flex justify-between">
            <span class="text-slate-400">🔬 Algoritmo:</span>
            <span :class="algorithmColors[selectedAlgorithm]">{{ algorithmNames[selectedAlgorithm] }}</span>
          </div>
          <div class="flex justify-between">
            <span class="text-slate-400">📊 Estado Original:</span>
            <span class="text-green-400">✓ Cargado</span>
          </div>
          <div class="flex justify-between">
            <span class="text-slate-400">⚙️ Estado Procesado:</span>
            <span :class="processedModel.vertices.length > 0 ? 'text-green-400' : (isProcessing ? 'text-yellow-400' : 'text-slate-400')">
              {{ processedModel.vertices.length > 0 ? '✓ Completado Exitosamente' : (isProcessing ? '⏳ Procesando...' : '⏸️ Listo para procesar') }}
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
            Arrastra un archivo <code class="bg-slate-700 px-2 py-1 rounded text-purple-400">.obj</code> para aplicar remeshing
          </p>
        </div>
      </div>
    </div>

    <!-- Controles centrales -->
    <div class="lg:col-span-1">
      <div class="bg-slate-800/50 backdrop-blur-sm rounded-xl p-6 border border-slate-700">
        <h3 class="text-xl font-semibold text-white mb-4 flex items-center">
          <svg class="w-5 h-5 mr-2 text-purple-400" fill="none" stroke="currentColor" viewBox="0 0 24 24">
            <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M12 6V4m0 2a2 2 0 100 4m0-4a2 2 0 110 4m-6 8a2 2 0 100-4m0 4a2 2 0 100 4m0-4v2m0-6V4m6 6v10m6-2a2 2 0 100-4m0 4a2 2 0 100 4m0-4v2m0-6V4"></path>
          </svg>
          Parámetros
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
              :min="originalModel.vertices.length > 0 ? Math.floor(originalModel.vertices.length * 0.1) : 100"
              :max="originalModel.vertices.length > 0 ? Math.floor(originalModel.vertices.length * 0.9) : 1000"
              class="w-full px-3 py-2 bg-slate-600 border border-slate-500 rounded-lg text-white text-sm focus:outline-none focus:border-purple-400"
              placeholder="Ej: 5000"
              :disabled="isProcessing"
            >
            <div v-if="originalModel.vertices.length > 0" class="text-xs text-slate-400 mt-1">
              Rango válido: {{ Math.floor(originalModel.vertices.length * 0.1).toLocaleString() }} - {{ Math.floor(originalModel.vertices.length * 0.9).toLocaleString() }}
            </div>
            <div class="mt-2 text-center text-sm text-slate-400">
              Factor equivalente: {{ manualVertices && originalModel.vertices.length > 0 ? (manualVertices / originalModel.vertices.length).toFixed(2) : '0.00' }}
            </div>
          </div>

          <!-- Botón de Procesamiento -->
          <div class="bg-slate-700/50 rounded-lg p-3">
            <button 
              @click="processModel"
              :disabled="originalModel.vertices.length === 0 || isProcessing || !isValidConfiguration"
              :class="[
                'w-full py-3 px-4 rounded-lg transition-colors text-white font-semibold text-sm flex items-center justify-center',
                originalModel.vertices.length === 0 || isProcessing || !isValidConfiguration 
                  ? 'bg-slate-600 cursor-not-allowed' 
                  : algorithmButtonColors[selectedAlgorithm].replace('hover:bg-', 'bg-').split(' ')[0] + ' hover:' + algorithmButtonColors[selectedAlgorithm].split(' ')[1]
              ]"
            >
              <svg v-if="!isProcessing" class="w-5 h-5 mr-2" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M14.828 14.828a4 4 0 01-5.656 0M9 10h1m4 0h1m-6 4h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z"></path>
              </svg>
              <svg v-else class="animate-spin w-5 h-5 mr-2" fill="none" viewBox="0 0 24 24">
                <circle class="opacity-25" cx="12" cy="12" r="10" stroke="currentColor" stroke-width="4"></circle>
                <path class="opacity-75" fill="currentColor" d="M4 12a8 8 0 018-8V0C5.373 0 0 5.373 0 12h4zm2 5.291A7.962 7.962 0 014 12H0c0 3.042 1.135 5.824 3 7.938l3-2.647z"></path>
              </svg>
              {{ isProcessing ? 'Procesando ' + algorithmNames[selectedAlgorithm] + '...' : 'Procesar con ' + algorithmNames[selectedAlgorithm] }}
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
              :disabled="originalModel.vertices.length === 0"
            >
              Resetear Cámaras
            </button>
            <input 
              ref="fileInput"
              type="file" 
              accept=".obj"
              @change="loadObjFile"
              class="hidden"
            />
            <button 
              @click="$refs.fileInput.click()"
              class="py-2 px-3 bg-purple-600 hover:bg-purple-500 rounded-lg transition-colors text-white font-medium text-sm"
              :disabled="isProcessing"
            >
              Cargar Modelo
            </button>
          </div>
        </div>
      </div>
    </div>

    <!-- Panel derecho: Información del algoritmo -->
    <div class="lg:col-span-1">
      <div class="bg-slate-800/50 backdrop-blur-sm rounded-xl p-6 border border-slate-700">
        <h3 class="text-xl font-semibold text-white mb-4 flex items-center">
          <svg class="w-5 h-5 mr-2 text-orange-400" fill="none" stroke="currentColor" viewBox="0 0 24 24">
            <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M13 16h-1v-4h-1m1-4h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z"></path>
          </svg>
          Algoritmo Actual
        </h3>
        
        <div class="space-y-3 text-sm text-slate-300">
          <div class="text-center mb-4">
            <div :class="['w-16 h-16 mx-auto mb-3 rounded-full flex items-center justify-center', algorithmBgColors[selectedAlgorithm]]">
              <svg class="w-8 h-8 text-white" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                <path v-if="selectedAlgorithm === 0" stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M4 6h16M4 12h16M4 18h16"></path>
                <path v-if="selectedAlgorithm === 1" stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M13 10V3L4 14h7v7l9-11h-7z"></path>
                <path v-if="selectedAlgorithm === 2" stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M7 16V4m0 0L3 8m4-4l4 4m6 0v12m0 0l4-4m-4 4l-4-4"></path>
                <path v-if="selectedAlgorithm === 3" stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M9.663 17h4.673M12 3v1m6.364 1.636l-.707.707M21 12h-1M4 12H3m3.343-5.657l-.707-.707m2.828 9.9a5 5 0 117.072 0l-.548.547A3.374 3.374 0 0014 18.469V19a2 2 0 11-4 0v-.531c0-.895-.356-1.754-.988-2.386l-.548-.547z"></path>
              </svg>
            </div>
            <h4 :class="['text-lg font-semibold mb-2', algorithmColors[selectedAlgorithm]]">{{ algorithmNames[selectedAlgorithm] }}</h4>
          </div>
          
          <div class="bg-slate-700 rounded-lg p-3">
            <h5 class="font-semibold text-white mb-2 text-xs">Características:</h5>
            <ul class="space-y-1 text-xs">
              <li v-if="selectedAlgorithm === 0">• Distribución homogénea de vértices</li>
              <li v-if="selectedAlgorithm === 0">• Procesamiento rápido y eficiente</li>
              <li v-if="selectedAlgorithm === 0">• Malla regular y predecible</li>
              
              <li v-if="selectedAlgorithm === 1">• Adaptación a curvatura local</li>
              <li v-if="selectedAlgorithm === 1">• Preservación de detalles importantes</li>
              <li v-if="selectedAlgorithm === 1">• Optimización inteligente de densidad</li>
              
              <li v-if="selectedAlgorithm === 2">• Orientación direccional de elementos</li>
              <li v-if="selectedAlgorithm === 2">• Seguimiento de flujo superficial</li>
              <li v-if="selectedAlgorithm === 2">• Elementos alargados eficientes</li>
              
              <li v-if="selectedAlgorithm === 3">• Métricas cuadráticas avanzadas</li>
              <li v-if="selectedAlgorithm === 3">• Optimización dual de orientación</li>
              <li v-if="selectedAlgorithm === 3">• Máxima precisión geométrica</li>
            </ul>
          </div>

          <div v-if="mensaje" :class="['rounded-lg p-2 border', algorithmMessageColors[selectedAlgorithm]]">
            <h4 :class="['font-semibold mb-1 text-xs', algorithmColors[selectedAlgorithm]]">Resultado:</h4>
            <p :class="['text-xs', algorithmColors[selectedAlgorithm]]">{{ mensaje }}</p>
          </div>

          <!-- Cronómetro en tiempo real -->
          <div v-if="isProcessing" class="bg-yellow-900/30 border border-yellow-500/30 rounded-lg p-3">
            <div class="flex items-center justify-center mb-2">
              <svg class="animate-spin w-6 h-6 text-yellow-400 mr-2" fill="none" viewBox="0 0 24 24">
                <circle class="opacity-25" cx="12" cy="12" r="10" stroke="currentColor" stroke-width="4"></circle>
                <path class="opacity-75" fill="currentColor" d="M4 12a8 8 0 018-8V0C5.373 0 0 5.373 0 12h4zm2 5.291A7.962 7.962 0 014 12H0c0 3.042 1.135 5.824 3 7.938l3-2.647z"></path>
              </svg>
              <span class="text-yellow-400 font-semibold text-sm">Procesando {{ algorithmNames[selectedAlgorithm] }}...</span>
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
        class="w-full h-80 bg-white rounded-lg overflow-hidden relative border-2 border-dashed border-slate-600 hover:border-purple-400 transition-colors duration-300 mb-4"
        @dragover.prevent 
        @drop="onDrop"
      >
        <div v-if="originalModel.vertices.length === 0" class="absolute inset-0 flex items-center justify-center bg-white">
          <div class="text-center text-slate-600">
            <svg class="w-16 h-16 mx-auto mb-4 opacity-50" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M7 16a4 4 0 01-.88-7.903A5 5 0 1115.9 6L16 6a5 5 0 011 9.9M15 13l-3-3m0 0l-3 3m3-3v12"></path>
            </svg>
            <p class="text-lg font-medium text-slate-700">Arrastra archivo .obj aquí</p>
            <p class="text-sm mt-2 text-slate-600">Remeshing avanzado con Voronoi</p>
          </div>
        </div>
      </div>

      <!-- Características del Modelo Original -->
      <div v-if="originalModel.vertices.length > 0" class="bg-slate-700 rounded-lg p-4">
        <h4 class="font-semibold text-blue-400 mb-3 text-center">📊 Malla Original</h4>
        <div class="grid grid-cols-2 gap-4 text-sm">
          <div class="text-center">
            <div class="text-2xl font-bold text-blue-400">{{ originalModel.vertices.length.toLocaleString() }}</div>
            <div class="text-xs text-slate-400">Vértices</div>
          </div>
          <div class="text-center">
            <div class="text-2xl font-bold text-blue-400">{{ originalModel.faces.length.toLocaleString() }}</div>
            <div class="text-xs text-slate-400">Caras</div>
          </div>
        </div>
      </div>

      <div v-if="originalModel.vertices.length > 0" class="mt-3 text-center text-sm text-slate-400">
        🖱️ Click y arrastra • 🔍 Scroll para zoom
      </div>
    </div>

    <!-- Modelo Procesado -->
    <div class="bg-slate-800/50 backdrop-blur-sm rounded-xl p-6 border border-slate-700">
      <h3 class="text-2xl font-semibold text-white mb-4 text-center flex items-center justify-center">
        <div :class="['w-4 h-4 rounded-full mr-3', algorithmDotColors[selectedAlgorithm]]"></div>
        Malla Procesada ({{ algorithmNames[selectedAlgorithm] }})
      </h3>
      
      <div 
        ref="processedContainer" 
        class="w-full h-80 bg-white rounded-lg overflow-hidden relative mb-4"
      >
        <div v-if="processedModel.vertices.length === 0" class="absolute inset-0 flex items-center justify-center bg-white z-10">
          <div class="text-center">
            <svg v-if="isProcessing" class="animate-spin w-12 h-12 mx-auto mb-4 text-slate-600" fill="none" viewBox="0 0 24 24">
              <circle class="opacity-25" cx="12" cy="12" r="10" stroke="currentColor" stroke-width="4"></circle>
              <path class="opacity-75" fill="currentColor" d="M4 12a8 8 0 018-8V0C5.373 0 0 5.373 0 12h4zm2 5.291A7.962 7.962 0 014 12H0c0 3.042 1.135 5.824 3 7.938l3-2.647z"></path>
            </svg>
            <svg v-else class="w-12 h-12 mx-auto mb-4 opacity-50 text-slate-600" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M19 11H5m14 0a2 2 0 012 2v6a2 2 0 01-2 2H5a2 2 0 01-2-2v-6a2 2 0 012-2m14 0V9a2 2 0 00-2-2M5 11V9a2 2 0 012-2m0 0V5a2 2 0 012-2h6a2 2 0 012 2v2M7 7h10"></path>
            </svg>
            <p class="text-lg font-medium text-slate-700">
              {{ isProcessing ? 'Aplicando ' + algorithmNames[selectedAlgorithm] + '...' : (originalModel.vertices.length > 0 ? 'Listo para procesar' : 'Carga un modelo primero') }}
            </p>
            <p v-if="isProcessing" class="text-sm mt-2 text-slate-600">
              Objetivo: {{ targetVertices.toLocaleString() }} vértices
            </p>
            <p v-if="isProcessing" class="text-lg font-mono mt-2 text-orange-600 font-bold">
              ⏱️ {{ elapsedTime }}s
            </p>
          </div>
        </div>
      </div>

      <!-- Características del Modelo Procesado -->
      <div v-if="processedModel.vertices.length > 0" class="bg-slate-700 rounded-lg p-4">
        <h4 :class="['font-semibold mb-3 text-center', algorithmColors[selectedAlgorithm]]">📊 Malla Procesada</h4>
        <div class="grid grid-cols-2 gap-4 text-sm">
          <div class="text-center">
            <div :class="['text-2xl font-bold', algorithmColors[selectedAlgorithm]]">{{ processedModel.vertices.length.toLocaleString() }}</div>
            <div class="text-xs text-slate-400">Vértices</div>
          </div>
          <div class="text-center">
            <div :class="['text-2xl font-bold', algorithmColors[selectedAlgorithm]]">{{ processedModel.faces.length.toLocaleString() }}</div>
            <div class="text-xs text-slate-400">Caras</div>
          </div>
        </div>

        <!-- Comparación -->
        <div class="mt-3 pt-3 border-t border-slate-600">
          <h5 :class="['text-xs mb-2 text-center', algorithmColors[selectedAlgorithm]]">📈 Resultado {{ algorithmNames[selectedAlgorithm] }}:</h5>
          <div class="grid grid-cols-2 gap-2 text-center">
            <div>
              <div class="text-slate-400 text-xs">Cambio en Vértices</div>
              <div :class="['font-mono text-sm', algorithmColors[selectedAlgorithm]]">
                {{ originalModel.vertices.length > 0 ? ((processedModel.vertices.length / originalModel.vertices.length) * 100).toFixed(1) : 0 }}%
              </div>
            </div>
            <div>
              <div class="text-slate-400 text-xs">Tiempo Procesamiento</div>
              <div :class="['font-mono text-sm', algorithmColors[selectedAlgorithm]]">{{ finalProcessingTime }}s</div>
            </div>
          </div>
        </div>

        <!-- Botón de descarga -->
        <div class="mt-3 pt-3 border-t border-slate-600">
          <button 
            @click="downloadProcessedModel"
            :class="['w-full py-2 px-4 rounded-lg transition-colors text-white font-medium text-sm flex items-center justify-center', algorithmButtonColors[selectedAlgorithm]]"
          >
            <svg class="w-4 h-4 mr-2" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M12 10v6m0 0l-4-4m4 4l4-4m-4-4V3"></path>
            </svg>
            Descargar {{ algorithmNames[selectedAlgorithm] }}
          </button>
        </div>
      </div>

      <div v-if="processedModel.vertices.length > 0" class="mt-3 text-center text-sm text-slate-400">
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
const selectedAlgorithm = ref(0)

// Configuración de algoritmos
const algorithmNames = ['Malla Homogénea', 'Malla Sensible a Curvatura', 'Malla Tensorial', 'Malla Cuádrica-Tensorial']
const algorithmColors = ['text-blue-400', 'text-green-400', 'text-purple-400', 'text-orange-400']
const algorithmBgColors = ['bg-blue-500', 'bg-green-500', 'bg-purple-500', 'bg-orange-500']
const algorithmDotColors = ['bg-blue-400', 'bg-green-400', 'bg-purple-400', 'bg-orange-400']
const algorithmButtonColors = ['bg-blue-600 hover:bg-blue-500', 'bg-green-600 hover:bg-green-500', 'bg-purple-600 hover:bg-purple-500', 'bg-orange-600 hover:bg-orange-500']
const algorithmMessageColors = ['bg-blue-900/30 border-blue-500/30', 'bg-green-900/30 border-green-500/30', 'bg-purple-900/30 border-purple-500/30', 'bg-orange-900/30 border-orange-500/30']

const originalModel = ref({
  name: '',
  vertices: [],
  faces: []
})

const processedModel = ref({
  name: '',
  vertices: [],
  faces: []
})

// Variable para almacenar el contenido OBJ original
let originalObjContent = ''
const processedObjContent = ref('')

// Variables Three.js
let originalScene, originalCamera, originalRenderer, originalControls
let processedScene, processedCamera, processedRenderer, processedControls
let objLoader
let animationId

// Computed properties
const targetVertices = computed(() => {
  if (originalModel.value.vertices.length === 0) return 0
  
  if (activeTab.value === 'factor') {
    return Math.floor(originalModel.value.vertices.length * reductionFactor.value)
  } else {
    return manualVertices.value || Math.floor(originalModel.value.vertices.length * reductionFactor.value)
  }
})

const isValidConfiguration = computed(() => {
  if (originalModel.value.vertices.length === 0) return false
  
  if (activeTab.value === 'factor') {
    return reductionFactor.value >= 0.1 && reductionFactor.value <= 0.9
  } else {
    const min = Math.floor(originalModel.value.vertices.length * 0.1)
    const max = Math.floor(originalModel.value.vertices.length * 0.9)
    return manualVertices.value && manualVertices.value >= min && manualVertices.value <= max
  }
})

// Watch para sincronizar tabs
watch(activeTab, (newTab) => {
  if (newTab === 'vertices' && originalModel.value.vertices.length > 0 && !manualVertices.value) {
    manualVertices.value = Math.floor(originalModel.value.vertices.length * reductionFactor.value)
  }
})

watch(manualVertices, (newValue) => {
  if (activeTab.value === 'vertices' && originalModel.value.vertices.length > 0 && newValue) {
    const newFactor = newValue / originalModel.value.vertices.length
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

function selectAlgorithm(index) {
  selectedAlgorithm.value = index
  mensaje.value = ''
  
  if (originalModel.value.vertices.length > 0 && processedModel.value.vertices.length > 0) {
    clearProcessedModel()
  }
}

function downloadProcessedModel() {
  if (!processedObjContent.value || !originalModel.value.name) {
    alert('No hay modelo procesado para descargar')
    return
  }
  
  const blob = new Blob([processedObjContent.value], { type: 'text/plain' })
  const url = URL.createObjectURL(blob)
  const link = document.createElement('a')
  link.href = url
  link.download = `${algorithmNames[selectedAlgorithm.value]}_${originalModel.value.name}`
  document.body.appendChild(link)
  link.click()
  document.body.removeChild(link)
  URL.revokeObjectURL(url)
}

onMounted(async () => {
  await nextTick()
  setTimeout(() => {
    initThreeJS()
  }, 100)
})

onUnmounted(() => {
  if (animationId) {
    cancelAnimationFrame(animationId)
  }
  if (processingTimer) clearInterval(processingTimer)
  if (originalRenderer) originalRenderer.dispose()
  if (processedRenderer) processedRenderer.dispose()
})

function clearProcessedModel() {
  processedModel.value = { name: '', vertices: [], faces: [] }
  processedObjContent.value = ''
  finalProcessingTime.value = 0
  
  if (processedScene) {
    while(processedScene.children.length > 0) {
      processedScene.remove(processedScene.children[0])
    }
    
    const processedLight = new THREE.DirectionalLight(0xffffff, 1)
    processedLight.position.set(1, 1, 1).normalize()
    processedScene.add(processedLight)
    
    if (processedRenderer && processedCamera) {
      processedScene.background = new THREE.Color(0xffffff)
      processedRenderer.render(processedScene, processedCamera)
    }
  }
}

function clearAllStates() {
  originalModel.value = { name: '', vertices: [], faces: [] }
  processedModel.value = { name: '', vertices: [], faces: [] }
  mensaje.value = ''
  isProcessing.value = false
  originalObjContent = ''
  processedObjContent.value = ''
  manualVertices.value = null
  elapsedTime.value = 0
  finalProcessingTime.value = 0
  
  if (processingTimer) {
    clearInterval(processingTimer)
    processingTimer = null
  }
  
  // Clear and force white background for both scenes
  if (originalScene && originalRenderer && originalCamera) {
    while(originalScene.children.length > 0) {
      originalScene.remove(originalScene.children[0])
    }
    const originalLight = new THREE.DirectionalLight(0xffffff, 1)
    originalLight.position.set(1, 1, 1).normalize()
    originalScene.add(originalLight)
    originalScene.background = new THREE.Color(0xffffff)
    originalRenderer.render(originalScene, originalCamera)
  }
  
  if (processedScene && processedRenderer && processedCamera) {
    while(processedScene.children.length > 0) {
      processedScene.remove(processedScene.children[0])
    }
    const processedLight = new THREE.DirectionalLight(0xffffff, 1)
    processedLight.position.set(1, 1, 1).normalize()
    processedScene.add(processedLight)
    processedScene.background = new THREE.Color(0xffffff)
    processedRenderer.render(processedScene, processedCamera)
  }
}

const initThreeJS = () => {
  objLoader = new OBJLoader()
  
  if (originalContainer.value) {
    const width = originalContainer.value.clientWidth
    const height = originalContainer.value.clientHeight

    originalScene = new THREE.Scene()
    originalScene.background = new THREE.Color(0xffffff)
    
    originalCamera = new THREE.PerspectiveCamera(75, width / height, 0.1, 1000)
    originalCamera.position.set(0, 0, 4)
    
    originalRenderer = new THREE.WebGLRenderer({ antialias: true })
    originalRenderer.setSize(width, height)
    originalContainer.value.appendChild(originalRenderer.domElement)
    
    const originalLight = new THREE.DirectionalLight(0xffffff, 1)
    originalLight.position.set(1, 1, 1).normalize()
    originalScene.add(originalLight)
    
    originalControls = new OrbitControls(originalCamera, originalRenderer.domElement)
    originalControls.enableDamping = true
    originalControls.dampingFactor = 0.05
    originalControls.autoRotate = false
    originalControls.autoRotateSpeed = 2.0
  }
  
  if (processedContainer.value) {
    const width = processedContainer.value.clientWidth
    const height = processedContainer.value.clientHeight

    processedScene = new THREE.Scene()
    processedScene.background = new THREE.Color(0xffffff)
    
    processedCamera = new THREE.PerspectiveCamera(75, width / height, 0.1, 1000)
    processedCamera.position.set(0, 0, 4)
    
    processedRenderer = new THREE.WebGLRenderer({ antialias: true })
    processedRenderer.setSize(width, height)
    processedContainer.value.appendChild(processedRenderer.domElement)
    
    const processedLight = new THREE.DirectionalLight(0xffffff, 1)
    processedLight.position.set(1, 1, 1).normalize()
    processedScene.add(processedLight)
    
    processedControls = new OrbitControls(processedCamera, processedRenderer.domElement)
    processedControls.enableDamping = true
    processedControls.dampingFactor = 0.05
    processedControls.autoRotate = false
    processedControls.autoRotateSpeed = 2.0
  }
  
  animate()
}

const animate = () => {
  animationId = requestAnimationFrame(animate)
  
  if (originalControls) {
    originalControls.update()
    originalRenderer.render(originalScene, originalCamera)
  }
  
  if (processedControls) {
    processedControls.update()
    processedRenderer.render(processedScene, processedCamera)
  }
}

const loadObjFile = async (event) => {
  const file = event.target.files[0]
  if (!file) return
  
  clearAllStates()
  
  try {
    const text = await file.text()
    originalObjContent = text
    const parsed = parseObjFile(text)
    
    originalModel.value = {
      name: file.name,
      vertices: parsed.vertices,
      faces: parsed.faces
    }
    
    const originalObject = objLoader.parse(text)
    
    while(originalScene.children.length > 0) {
      originalScene.remove(originalScene.children[0])
    }
    
    const originalLight = new THREE.DirectionalLight(0xffffff, 1)
    originalLight.position.set(1, 1, 1).normalize()
    originalScene.add(originalLight)
    
    const material = new THREE.MeshLambertMaterial({ 
      color: 0x61dafb,
      wireframe: wireframeMode.value,
      transparent: false,
      opacity: 1.0,
      side: THREE.DoubleSide
    })
    originalObject.traverse(child => {
      if (child.isMesh) {
        child.material = material
        child.geometry.computeVertexNormals()
      }
    })
    
    originalScene.add(originalObject)
    
    const boundingBox = new THREE.Box3().setFromObject(originalObject)
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
    
  } catch (error) {
    console.error('Error cargando archivo OBJ:', error)
    alert('Error al cargar el archivo. Asegúrate de que sea un archivo .obj válido.')
  }
}

const processModel = async () => {
  if (!originalObjContent || !originalModel.value.name || !isValidConfiguration.value) {
    return
  }

  isProcessing.value = true
  processedModel.value = { name: '', vertices: [], faces: [] }
  mensaje.value = `Iniciando ${algorithmNames[selectedAlgorithm.value]}...`
  
  // Force white background immediately when processing starts
  if (processedScene && processedRenderer && processedCamera) {
    processedScene.background = new THREE.Color(0xffffff)
    processedRenderer.render(processedScene, processedCamera)
  }
  
  // Iniciar cronómetro
  startTimer()
  
  try {
    const res = await fetch('http://localhost:3001/api/voronoi', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ 
        modo: selectedAlgorithm.value,
        obj: originalObjContent,
        nombre: originalModel.value.name.replace('.obj', ''),
        targetVertices: targetVertices.value
      })
    })

    if (!res.ok) {
      throw new Error(`HTTP error! status: ${res.status}`)
    }

    const data = await res.json()
    
    if (data.error) {
      throw new Error(data.error)
    }
    
    const modelName = originalModel.value.name.replace('.obj', '')
    if (data.stdout && data.stdout.trim()) {
      mensaje.value = `✅ ${algorithmNames[selectedAlgorithm.value]} completado exitosamente para ${modelName}`
    } else {
      mensaje.value = `✅ ${algorithmNames[selectedAlgorithm.value]} procesado exitosamente para ${modelName}`
    }
    
    if (data.obj) {
      processedObjContent.value = data.obj
      
      const parsed = parseObjFile(data.obj)
      processedModel.value = {
        name: `${algorithmNames[selectedAlgorithm.value]}_${originalModel.value.name}`,
        vertices: parsed.vertices,
        faces: parsed.faces
      }
      
      const processedObject = objLoader.parse(data.obj)
      
      while (processedScene.children.length > 0) {
        processedScene.remove(processedScene.children[0])
      }
      
      const processedLight = new THREE.DirectionalLight(0xffffff, 1)
      processedLight.position.set(1, 1, 1).normalize()
      processedScene.add(processedLight)
      
      const algorithmMaterialColors = [0x3b82f6, 0x22c55e, 0x8b5cf6, 0xf97316]
      
      const material = new THREE.MeshLambertMaterial({ 
        color: algorithmMaterialColors[selectedAlgorithm.value],
        wireframe: wireframeMode.value,
        transparent: false,
        opacity: 1.0,
        side: THREE.DoubleSide
      })

      processedObject.traverse(child => {
        if (child.isMesh) {
          child.material = material
          child.geometry.computeVertexNormals()
        }
      })
      
      processedScene.add(processedObject)
      
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
    }
    
  } catch (error) {
    console.error('Error procesando modelo:', error)
    mensaje.value = `❌ Error procesando ${algorithmNames[selectedAlgorithm.value]}: ${error.message}`
  } finally {
    isProcessing.value = false
    stopTimer()
  }
}

const parseObjFile = (text) => {
  const vertices = []
  const faces = []
  
  const lines = text.split('\n')
  
  for (const line of lines) {
    const parts = line.trim().split(/\s+/)
    
    if (parts[0] === 'v') {
      const x = parseFloat(parts[1])
      const y = parseFloat(parts[2])
      const z = parseFloat(parts[3])
      vertices.push([x, y, z])
    } else if (parts[0] === 'f') {
      const faceVertices = []
      for (let i = 1; i < parts.length; i++) {
        const vertexIndex = parseInt(parts[i].split('/')[0]) - 1
        faceVertices.push(vertexIndex)
      }
      faces.push(faceVertices)
    }
  }
  
  return { vertices, faces }
}

const onDrop = (event) => {
  event.preventDefault()
  const file = event.dataTransfer.files[0]
  
  if (!file || !file.name.endsWith('.obj')) {
    alert('Por favor arrastra un archivo .obj válido.')
    return
  }

  clearAllStates()

  const fakeEvent = { target: { files: [file] } }
  loadObjFile(fakeEvent)
}

function resetCameras() {
  if (originalModel.value.vertices.length > 0 && originalScene.children.length > 0) {
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
  
  if (processedModel.value.vertices.length > 0 && processedScene.children.length > 0) {
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
  background-color: #8b5cf6;
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

.slider::-webkit-slider-thumb {
  appearance: none;
  height: 20px;
  width: 20px;
  border-radius: 50%;
  background: #8b5cf6;
  cursor: pointer;
  border: 2px solid #1e293b;
}

.slider::-moz-range-thumb {
  height: 20px;
  width: 20px;
  border-radius: 50%;
  background: #8b5cf6;
  cursor: pointer;
  border: 2px solid #1e293b;
}
</style>
