<template>
  <div class="max-w-6xl mx-auto">
    <!-- Hero Section -->
    <div class="text-center mb-16">
      <h1 class="text-6xl font-bold text-white mb-6 bg-gradient-to-r from-blue-400 via-purple-500 to-green-400 bg-clip-text text-transparent">
        Herramienta de Remeshing 3D Avanzado
      </h1>
      <p class="text-xl text-slate-300 mb-8 leading-relaxed max-w-4xl mx-auto">
        Plataforma especializada en remeshing de modelos 3D con algoritmos de vanguardia: 
        <strong class="text-blue-400">Quadric Error Metrics</strong> y 
        <strong class="text-purple-400">Diagramas de Voronoi</strong>
      </p>
      <div class="flex justify-center space-x-4">
        <router-link 
          to="/modelo1"
          class="bg-gradient-to-r from-blue-600 to-blue-700 hover:from-blue-700 hover:to-blue-800 text-white px-8 py-3 rounded-lg font-semibold transition-all duration-300 transform hover:scale-105 flex items-center"
        >
          <svg class="w-5 h-5 mr-2" fill="none" stroke="currentColor" viewBox="0 0 24 24">
            <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M13 10V3L4 14h7v7l9-11h-7z"></path>
          </svg>
          QEM Remeshing
        </router-link>
        <router-link 
          to="/modelo2"
          class="bg-gradient-to-r from-purple-600 to-purple-700 hover:from-purple-700 hover:to-purple-800 text-white px-8 py-3 rounded-lg font-semibold transition-all duration-300 transform hover:scale-105 flex items-center"
        >
          <svg class="w-5 h-5 mr-2" fill="none" stroke="currentColor" viewBox="0 0 24 24">
            <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M19 11H5m14 0a2 2 0 012 2v6a2 2 0 01-2 2H5a2 2 0 01-2-2v-6a2 2 0 012-2m14 0V9a2 2 0 00-2-2M5 11V9a2 2 0 012-2m0 0V5a2 2 0 012-2h6a2 2 0 012 2v2M7 7h10"></path>
          </svg>
          Voronoi Remeshing
        </router-link>
      </div>
    </div>

    <!-- Algoritmos Principales -->
    <div class="mb-16">
      <h2 class="text-4xl font-bold text-white mb-8 text-center">Algoritmos Implementados</h2>
      
      <div class="grid lg:grid-cols-2 gap-8">
        <!-- QEM Algorithm -->
        <div class="bg-slate-800/50 backdrop-blur-sm rounded-xl p-8 border border-slate-700 hover:border-blue-400 transition-colors">
          <div class="flex items-center mb-6">
            <div class="w-16 h-16 bg-blue-600 rounded-xl flex items-center justify-center mr-4">
              <svg class="w-8 h-8 text-white" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M13 10V3L4 14h7v7l9-11h-7z"></path>
              </svg>
            </div>
            <div>
              <h3 class="text-2xl font-bold text-white">Quadric Error Metrics</h3>
              <p class="text-blue-400 font-medium">Simplificación Inteligente</p>
            </div>
          </div>
          
          <div class="space-y-4 text-slate-300">
            <p class="leading-relaxed">
              Algoritmo de <strong class="text-blue-400">simplificación de superficies</strong> notable por su 
              <strong>eficiencia</strong> y <strong>rapidez</strong>. Utiliza matrices cuadráticas para 
              determinar qué vértices colapsar preservando la forma original.
            </p>
            
            <div class="bg-slate-700/50 rounded-lg p-4">
              <h4 class="font-semibold text-white mb-3 text-sm">🔧 Proceso QEM:</h4>
              <ul class="space-y-2 text-sm">
                <li class="flex items-start">
                  <span class="w-2 h-2 bg-blue-400 rounded-full mt-2 mr-3 flex-shrink-0"></span>
                  Calcula error cuadrático para cada vértice
                </li>
                <li class="flex items-start">
                  <span class="w-2 h-2 bg-blue-400 rounded-full mt-2 mr-3 flex-shrink-0"></span>
                  Evalúa costo de colapso de aristas
                </li>
                <li class="flex items-start">
                  <span class="w-2 h-2 bg-blue-400 rounded-full mt-2 mr-3 flex-shrink-0"></span>
                  Colapsa aristas con menor error
                </li>
                <li class="flex items-start">
                  <span class="w-2 h-2 bg-blue-400 rounded-full mt-2 mr-3 flex-shrink-0"></span>
                  Preserva características importantes
                </li>
              </ul>
            </div>

            <div class="bg-blue-900/20 border border-blue-500/30 rounded-lg p-4">
              <h4 class="font-semibold text-blue-400 mb-2 text-sm">⚡ Rendimiento:</h4>
              <ul class="space-y-1 text-sm">
                <li>• Tiempos de ejecución <strong>&lt; 4 segundos</strong> en todos los modelos</li>
                <li>• Complejidad cercana a <strong>O(n log n)</strong></li>
                <li>• Eficiente incluso con modelos de 125K+ vértices</li>
                <li>• Cada vértice almacena solo 10 valores de punto flotante</li>
              </ul>
            </div>
          </div>
        </div>

        <!-- Voronoi Algorithm -->
        <div class="bg-slate-800/50 backdrop-blur-sm rounded-xl p-8 border border-slate-700 hover:border-purple-400 transition-colors">
          <div class="flex items-center mb-6">
            <div class="w-16 h-16 bg-purple-600 rounded-xl flex items-center justify-center mr-4">
              <svg class="w-8 h-8 text-white" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M19 11H5m14 0a2 2 0 012 2v6a2 2 0 01-2 2H5a2 2 0 01-2-2v-6a2 2 0 012-2m14 0V9a2 2 0 00-2-2M5 11V9a2 2 0 012-2m0 0V5a2 2 0 012-2h6a2 2 0 012 2v2M7 7h10"></path>
              </svg>
            </div>
            <div>
              <h3 class="text-2xl font-bold text-white">Diagramas de Voronoi</h3>
              <p class="text-purple-400 font-medium">Remeshing Avanzado</p>
            </div>
          </div>
          
          <div class="space-y-4 text-slate-300">
            <p class="leading-relaxed">
              Enfoque basado en <strong class="text-purple-400">Diagramas de Voronoi Discretos</strong> 
              dependientes de métricas. Realiza múltiples ciclos de optimización geométrica con 
              <strong>4 variantes especializadas</strong>.
            </p>
            
            <div class="bg-slate-700/50 rounded-lg p-4">
              <h4 class="font-semibold text-white mb-3 text-sm">🎯 Variantes Disponibles:</h4>
              <div class="grid grid-cols-2 gap-2 text-xs">
                <div class="flex items-center">
                  <span class="w-2 h-2 bg-blue-400 rounded-full mr-2"></span>
                  Malla Homogénea
                </div>
                <div class="flex items-center">
                  <span class="w-2 h-2 bg-green-400 rounded-full mr-2"></span>
                  Sensible a Curvatura
                </div>
                <div class="flex items-center">
                  <span class="w-2 h-2 bg-purple-400 rounded-full mr-2"></span>
                  Malla Tensorial
                </div>
                <div class="flex items-center">
                  <span class="w-2 h-2 bg-orange-400 rounded-full mr-2"></span>
                  Cuádrica-Tensorial
                </div>
              </div>
            </div>

            <div class="bg-purple-900/20 border border-purple-500/30 rounded-lg p-4">
              <h4 class="font-semibold text-purple-400 mb-2 text-sm">🔬 Características:</h4>
              <ul class="space-y-1 text-sm">
                <li>• Optimización basada en <strong>Lloyd</strong> y partición iterativa</li>
                <li>• Métricas <strong>isotrópicas</strong> y <strong>anisotrópicas</strong></li>
                <li>• Preservación de características afiladas con <strong>QEM</strong></li>
                <li>• Convergencia garantizada y paralelizable</li>
              </ul>
            </div>
          </div>
        </div>
      </div>
    </div>

    <!-- Análisis de Rendimiento -->
    <div class="mb-16">
      <h2 class="text-4xl font-bold text-white mb-8 text-center">Análisis de Rendimiento</h2>
      
      <div class="bg-slate-800/50 backdrop-blur-sm rounded-xl p-8 border border-slate-700 mb-8">
        <h3 class="text-2xl font-semibold text-white mb-6">Comparación de Eficiencia</h3>
        
        <div class="grid lg:grid-cols-2 gap-8">
          <div class="space-y-4">
            <h4 class="text-xl font-semibold text-blue-400 text-center">🚀 Quadric Error Metrics</h4>
            <div class="bg-blue-900/20 rounded-lg p-4">
              <img 
                src="./images/q.png" 
                alt="Gráfica de rendimiento QEM - Tiempos de procesamiento para diferentes modelos" 
                class="w-full h-auto rounded-lg mb-4"
              />
              <div class="p-3 bg-slate-700/50 rounded">
                <p class="text-xs text-slate-400">
                  <strong class="text-blue-400">Ventaja:</strong> Algoritmo incremental basado en colapsos de aristas 
                  con estructuras eficientes tipo heap. Mantiene comportamiento O(n log n).
                </p>
              </div>
            </div>
          </div>

          <div class="space-y-4">
            <h4 class="text-xl font-semibold text-purple-400 text-center">🔄 Voronoi Remeshing</h4>
            <div class="bg-purple-900/20 rounded-lg p-4">
              <img 
                src="./images/v.png" 
                alt="Gráfica de rendimiento Voronoi - Tiempos de procesamiento por algoritmo" 
                class="w-full h-auto rounded-lg mb-4"
              />
              <div class="p-3 bg-slate-700/50 rounded">
                <p class="text-xs text-slate-400">
                  <strong class="text-purple-400">Ventaja:</strong> Mayor control sobre la calidad final 
                  y distribución de elementos. Ideal para casos que requieren máxima precisión.
                </p>
              </div>
            </div>
          </div>
        </div>
      </div>

      <!-- Factores de Rendimiento -->
      <div class="grid md:grid-cols-2 gap-8">
        <div class="bg-slate-800/50 backdrop-blur-sm rounded-xl p-6 border border-slate-700">
          <h4 class="text-lg font-semibold text-white mb-4 flex items-center">
            <svg class="w-5 h-5 mr-2 text-blue-400" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M13 10V3L4 14h7v7l9-11h-7z"></path>
            </svg>
            Factores QEM
          </h4>
          <ul class="space-y-3 text-sm text-slate-300">
            <li class="flex items-start">
              <span class="w-2 h-2 bg-blue-400 rounded-full mt-2 mr-3 flex-shrink-0"></span>
              <div>
                <strong>Complejidad del Modelo:</strong> Directamente relacionada con el número de caras
              </div>
            </li>
            <li class="flex items-start">
              <span class="w-2 h-2 bg-blue-400 rounded-full mt-2 mr-3 flex-shrink-0"></span>
              <div>
                <strong>Tiempo de Inicialización:</strong> Cálculo de matrices Q y selección de pares
              </div>
            </li>
            <li class="flex items-start">
              <span class="w-2 h-2 bg-blue-400 rounded-full mt-2 mr-3 flex-shrink-0"></span>
              <div>
                <strong>Parámetro de Umbral:</strong> Valores altos mejoran calidad pero aumentan complejidad
              </div>
            </li>
          </ul>
        </div>

        <div class="bg-slate-800/50 backdrop-blur-sm rounded-xl p-6 border border-slate-700">
          <h4 class="text-lg font-semibold text-white mb-4 flex items-center">
            <svg class="w-5 h-5 mr-2 text-purple-400" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M19 11H5m14 0a2 2 0 012 2v6a2 2 0 01-2 2H5a2 2 0 01-2-2v-6a2 2 0 012-2m14 0V9a2 2 0 00-2-2M5 11V9a2 2 0 012-2m0 0V5a2 2 0 012-2h6a2 2 0 012 2v2M7 7h10"></path>
            </svg>
            Factores Voronoi
          </h4>
          <ul class="space-y-3 text-sm text-slate-300">
            <li class="flex items-start">
              <span class="w-2 h-2 bg-purple-400 rounded-full mt-2 mr-3 flex-shrink-0"></span>
              <div>
                <strong>Tipo de Métrica:</strong> Isotrópica vs Anisotrópica afecta significativamente
              </div>
            </li>
            <li class="flex items-start">
              <span class="w-2 h-2 bg-purple-400 rounded-full mt-2 mr-3 flex-shrink-0"></span>
              <div>
                <strong>Cálculo de Curvatura:</strong> Análisis de campos direccionales y tensores
              </div>
            </li>
            <li class="flex items-start">
              <span class="w-2 h-2 bg-purple-400 rounded-full mt-2 mr-3 flex-shrink-0"></span>
              <div>
                <strong>Iteraciones Lloyd:</strong> Convergencia garantizada pero costosa
              </div>
            </li>
          </ul>
        </div>
      </div>
    </div>

    <!-- Casos de Uso -->
    <div class="mb-16">
      <h2 class="text-4xl font-bold text-white mb-8 text-center">Casos de Uso Recomendados</h2>
      
      <div class="grid lg:grid-cols-2 gap-8">
        <!-- QEM Use Cases -->
        <div class="bg-slate-800/50 backdrop-blur-sm rounded-xl p-8 border border-slate-700">
          <h3 class="text-2xl font-semibold text-blue-400 mb-6">🚀 Cuándo usar QEM</h3>
          
          <div class="space-y-6">
            <div class="bg-blue-900/20 border border-blue-500/30 rounded-lg p-4">
              <h4 class="font-semibold text-white mb-2">✅ Ideal para:</h4>
              <ul class="space-y-2 text-sm text-slate-300">
                <li>• <strong>Simplificación rápida</strong> de modelos complejos</li>
                <li>• <strong>Preservación de características</strong> geométricas críticas</li>
                <li>• <strong>Aplicaciones en tiempo real</strong> o interactivas</li>
                <li>• <strong>Modelos de gran tamaño</strong> (100K+ vértices)</li>
                <li>• <strong>Pipelines de optimización</strong> automática</li>
              </ul>
            </div>

            <div class="bg-slate-700/50 rounded-lg p-4">
              <h4 class="font-semibold text-slate-300 mb-2">🎯 Ejemplos de aplicación:</h4>
              <ul class="space-y-1 text-sm text-slate-400">
                <li>• Videojuegos (LOD - Level of Detail)</li>
                <li>• Visualización web 3D</li>
                <li>• Modelos para impresión 3D</li>
                <li>• Simulaciones físicas</li>
              </ul>
            </div>
          </div>
        </div>

        <!-- Voronoi Use Cases -->
        <div class="bg-slate-800/50 backdrop-blur-sm rounded-xl p-8 border border-slate-700">
          <h3 class="text-2xl font-semibold text-purple-400 mb-6">🔬 Cuándo usar Voronoi</h3>
          
          <div class="space-y-6">
            <div class="bg-purple-900/20 border border-purple-500/30 rounded-lg p-4">
              <h4 class="font-semibold text-white mb-2">✅ Ideal para:</h4>
              <ul class="space-y-2 text-sm text-slate-300">
                <li>• <strong>Máxima calidad</strong> de malla final</li>
                <li>• <strong>Distribución uniforme</strong> de elementos</li>
                <li>• <strong>Análisis de elementos finitos</strong> (FEA)</li>
                <li>• <strong>Simulaciones CFD</strong> (Computational Fluid Dynamics)</li>
                <li>• <strong>Modelos científicos</strong> de alta precisión</li>
              </ul>
            </div>

            <div class="bg-slate-700/50 rounded-lg p-4">
              <h4 class="font-semibold text-slate-300 mb-2">🎯 Variantes especializadas:</h4>
              <ul class="space-y-1 text-sm text-slate-400">
                <li>• <strong class="text-blue-400">Homogénea:</strong> Modelos simples, procesamiento rápido</li>
                <li>• <strong class="text-green-400">Adaptiva:</strong> Geometría compleja con curvatura variable</li>
                <li>• <strong class="text-purple-400">Tensorial:</strong> Superficies fluidas, direcciones preferenciales</li>
                <li>• <strong class="text-orange-400">Cuádrica-Tensorial:</strong> Máxima precisión, características críticas</li>
              </ul>
            </div>
          </div>
        </div>
      </div>
    </div>

    <!-- Características Técnicas -->
    <div class="mb-16">
      <h2 class="text-4xl font-bold text-white mb-8 text-center">Características Técnicas</h2>
      
      <div class="grid md:grid-cols-2 lg:grid-cols-4 gap-6">
        <div class="bg-slate-800/50 backdrop-blur-sm rounded-xl p-6 border border-slate-700">
          <div class="w-12 h-12 bg-green-600 rounded-lg flex items-center justify-center mb-4">
            <svg class="w-6 h-6 text-white" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M9 12l2 2 4-4m6 2a9 9 0 11-18 0 9 9 0 0118 0z"></path>
            </svg>
          </div>
          <h3 class="text-lg font-semibold text-white mb-2">Formatos</h3>
          <ul class="text-slate-400 text-sm space-y-1">
            <li>• Archivos .obj (Wavefront)</li>
            <li>• Vértices y caras</li>
            <li>• Modelos complejos</li>
            <li>• Alta resolución</li>
          </ul>
        </div>

        <div class="bg-slate-800/50 backdrop-blur-sm rounded-xl p-6 border border-slate-700">
          <div class="w-12 h-12 bg-blue-600 rounded-lg flex items-center justify-center mb-4">
            <svg class="w-6 h-6 text-white" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M15 12a3 3 0 11-6 0 3 3 0 016 0z"></path>
            </svg>
          </div>
          <h3 class="text-lg font-semibold text-white mb-2">Visualización</h3>
          <ul class="text-slate-400 text-sm space-y-1">
            <li>• Three.js WebGL</li>
            <li>• Controles de órbita</li>
            <li>• Modo wireframe</li>
            <li>• Rotación automática</li>
          </ul>
        </div>

        <div class="bg-slate-800/50 backdrop-blur-sm rounded-xl p-6 border border-slate-700">
          <div class="w-12 h-12 bg-purple-600 rounded-lg flex items-center justify-center mb-4">
            <svg class="w-6 h-6 text-white" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M9 19v-6a2 2 0 00-2-2H5a2 2 0 00-2 2v6a2 2 0 002 2h2a2 2 0 002-2zm0 0V9a2 2 0 012-2h2a2 2 0 012 2v10m-6 0a2 2 0 002 2h2a2 2 0 002-2m0 0V5a2 2 0 012-2h2a2 2 0 012 2v4a2 2 0 01-2 2h-2a2 2 0 00-2 2z"></path>
            </svg>
          </div>
          <h3 class="text-lg font-semibold text-white mb-2">Análisis</h3>
          <ul class="text-slate-400 text-sm space-y-1">
            <li>• Métricas detalladas</li>
            <li>• Estadísticas geométricas</li>
            <li>• Comparación lado a lado</li>
            <li>• Tiempo de procesamiento</li>
          </ul>
        </div>

        <div class="bg-slate-800/50 backdrop-blur-sm rounded-xl p-6 border border-slate-700">
          <div class="w-12 h-12 bg-orange-600 rounded-lg flex items-center justify-center mb-4">
            <svg class="w-6 h-6 text-white" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M12 10v6m0 0l-4-4m4 4l4-4m-4-4V3"></path>
            </svg>
          </div>
          <h3 class="text-lg font-semibold text-white mb-2">Exportación</h3>
          <ul class="text-slate-400 text-sm space-y-1">
            <li>• Descarga directa</li>
            <li>• Formato .obj</li>
            <li>• Modelos optimizados</li>
            <li>• Preservación de calidad</li>
          </ul>
        </div>
      </div>
    </div>

    <!-- Guía de Uso -->
    <div class="bg-slate-800/50 backdrop-blur-sm rounded-xl p-8 border border-slate-700 mb-16">
      <h2 class="text-3xl font-bold text-white mb-8 text-center">Guía de Uso</h2>
      
      <div class="space-y-8">
        <div class="flex items-start space-x-6">
          <div class="w-12 h-12 bg-blue-600 rounded-full flex items-center justify-center text-white font-bold text-lg flex-shrink-0">1</div>
          <div>
            <h3 class="text-xl font-semibold text-white mb-3">Carga tu Modelo 3D</h3>
            <p class="text-slate-300 mb-4">
              Arrastra tu archivo .obj al área de visualización o usa el botón "Cargar Modelo". 
              El modelo se cargará instantáneamente con Three.js y podrás explorarlo con los controles de órbita.
            </p>
            <div class="bg-slate-700/50 rounded-lg p-3">
              <p class="text-sm text-slate-400">
                <strong class="text-blue-400">Tip:</strong> Los modelos se visualizan automáticamente con estadísticas 
                detalladas incluyendo número de vértices, caras, aristas y dimensiones del bounding box.
              </p>
            </div>
          </div>
        </div>

        <div class="flex items-start space-x-6">
          <div class="w-12 h-12 bg-purple-600 rounded-full flex items-center justify-center text-white font-bold text-lg flex-shrink-0">2</div>
          <div>
            <h3 class="text-xl font-semibold text-white mb-3">Configura los Parámetros</h3>
            <p class="text-slate-300 mb-4">
              Selecciona el algoritmo deseado y ajusta los parámetros usando los tabs "Por Factor" o "Por Vértices". 
              Puedes especificar un factor de reducción (0.1-0.9) o un número exacto de vértices objetivo.
            </p>
            <div class="bg-slate-700/50 rounded-lg p-3">
              <p class="text-sm text-slate-400">
                <strong class="text-purple-400">Tip:</strong> El sistema calcula automáticamente el equivalente 
                entre factor y número de vértices, y valida que esté dentro del rango permitido.
              </p>
            </div>
          </div>
        </div>

        <div class="flex items-start space-x-6">
          <div class="w-12 h-12 bg-green-600 rounded-full flex items-center justify-center text-white font-bold text-lg flex-shrink-0">3</div>
          <div>
            <h3 class="text-xl font-semibold text-white mb-3">Procesa y Analiza</h3>
            <p class="text-slate-300 mb-4">
              Haz clic en "Procesar" para ejecutar el algoritmo seleccionado. El cronómetro mostrará el tiempo 
              real de procesamiento. Una vez completado, compara los resultados lado a lado con métricas detalladas.
            </p>
            <div class="bg-slate-700/50 rounded-lg p-3">
              <p class="text-sm text-slate-400">
                <strong class="text-green-400">Tip:</strong> Usa los controles de wireframe y rotación automática 
                para analizar mejor la calidad de la malla resultante. Descarga el modelo optimizado cuando estés satisfecho.
              </p>
            </div>
          </div>
        </div>
      </div>
    </div>

    <!-- Conclusión -->
    <div class="text-center bg-gradient-to-r from-slate-800/50 to-slate-700/50 backdrop-blur-sm rounded-xl p-8 border border-slate-700">
      <h2 class="text-3xl font-bold text-white mb-4">Comienza tu Proyecto de Remeshing</h2>
      <p class="text-slate-300 mb-6 max-w-3xl mx-auto">
        Esta herramienta combina la <strong class="text-blue-400">eficiencia del QEM</strong> con la 
        <strong class="text-purple-400">precisión del Voronoi</strong>, ofreciendo una solución completa 
        para optimización de mallas 3D. Ideal tanto para aplicaciones industriales como investigación académica.
      </p>
      <div class="flex justify-center space-x-4">
        <router-link 
          to="/modelo1"
          class="bg-blue-600 hover:bg-blue-700 text-white px-6 py-3 rounded-lg font-semibold transition-colors"
        >
          Probar QEM
        </router-link>
        <router-link 
          to="/modelo2"
          class="bg-purple-600 hover:bg-purple-700 text-white px-6 py-3 rounded-lg font-semibold transition-colors"
        >
          Probar Voronoi
        </router-link>
      </div>
    </div>
  </div>
</template>
