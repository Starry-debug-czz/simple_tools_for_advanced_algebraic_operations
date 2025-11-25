// Linear Algebra Code World - Main JavaScript
class LinearAlgebraWorld {
    constructor() {
        this.currentLang = 'en';
        this.translations = {
            en: {
                navTitle: 'Linear Algebra World',
                enterText: 'Enter the Matrix',
                mainTitle: 'Welcome to czz\'s',
                subTitle: 'Linear Algebra Code World',
                typedText: 'Explore the infinite possibilities of matrix operations in a cyberpunk universe...',
                feature1Title: 'Matrix Operations',
                feature1Desc: 'Advanced matrix calculations with step-by-step visualization',
                feature2Title: 'Quadratic Forms',
                feature2Desc: 'Transform and analyze quadratic forms with precision',
                feature3Title: 'Cosmic Interface',
                feature3Desc: 'Immersive futuristic design with interactive elements',
                aboutTitle: 'About This Platform',
                aboutDesc: 'This platform is designed to showcase the code of a linear algebra function calculator I developed recently. It also serves as a practical tool for those in need, providing calculation insights and enabling users to verify their own calculation processes. ——Chenzhizhong',
                stat1: 'Functions',
                stat2: 'Calculations',
                stat3: 'Languages',
                stat4: 'Limits',
                footerText: '© 2025 czz\'s Linear Algebra Code World',
                footerDesc: 'Where mathematics meets the future'
            },
            zh: {
                navTitle: '线性代数世界',
                enterText: '进入矩阵',
                mainTitle: '欢迎来到czz的',
                subTitle: '线性代数代码世界',
                typedText: '在赛博朋克宇宙中探索矩阵运算的无限可能...',
                feature1Title: '矩阵运算',
                feature1Desc: '带有逐步可视化的高级矩阵计算',
                feature2Title: '二次型',
                feature2Desc: '精确转换和分析二次型',
                feature3Title: '宇宙界面',
                feature3Desc: '具有交互元素的沉浸式未来设计',
                aboutTitle: '关于本平台',
                aboutDesc: '本平台用于展示本人前不久编写的线性代数功能计算器的代码同时供所需之人使用，用于提供计算思路，检验自我的计算过程 ——Chen Zhizhong',
                stat1: '功能',
                stat2: '计算',
                stat3: '语言',
                stat4: '限制',
                footerText: '© 2025 czz的线性代数代码世界',
                footerDesc: '数学与未来相遇的地方'
            }
        };

        this.init();
    }

    init() {
        this.createParticles();
        this.initTypewriter();
        this.initLanguageToggle();
        this.initScrollAnimations();
        this.initNavigation();
        this.initHoverEffects();
        this.initMouseEffects();
        this.initGalaxyBackground();
    }

    createParticles() {
        const particleContainer = document.getElementById('particles');
        const particleCount = 100;

        for (let i = 0; i < particleCount; i++) {
            const particle = document.createElement('div');
            particle.className = 'particle';
            particle.style.left = Math.random() * 100 + '%';
            particle.style.animationDelay = Math.random() * 6 + 's';
            particle.style.animationDuration = (Math.random() * 4 + 4) + 's';

            // Random colors between neon blue and fluorescent green
            const colors = [
                '#00CCFF', '#0099FF', '#0066FF', // 蓝色系
                '#6C00FF', '#8A2BE2', '#9370DB', // 紫色系
                '#00FFC6', '#00FF9D', '#00FF73', // 绿色系
                '#FFFFFF', '#E6E6FA' // 白色和淡紫色
            ];
            particle.style.background = colors[Math.floor(Math.random() * colors.length)];
            // 随机大小
            const size = Math.random() * 3 + 1;
            particle.style.width = size + 'px';
            particle.style.height = size + 'px';

            // 添加发光效果
            particle.style.boxShadow = `0 0 ${size * 2}px currentColor`;
            particleContainer.appendChild(particle);
        }
    }

    initTypewriter() {
        const typedElement = document.getElementById('typed-text');
        if (typedElement) {
            new Typed('#typed-text', {
                strings: [this.translations[this.currentLang].typedText],
                typeSpeed: 50,
                startDelay: 2000,
                showCursor: true,
                cursorChar: '_'
            });
        }
    }

    initLanguageToggle() {
        const langToggle = document.getElementById('langToggle');
        const langSlider = document.getElementById('langSlider');

        if (langToggle && langSlider) {
            langToggle.addEventListener('click', () => {
                this.currentLang = this.currentLang === 'en' ? 'zh' : 'en';
                this.updateLanguage();

                // Animate slider
                const translateX = this.currentLang === 'zh' ? 80 : 0;
                langSlider.style.transform = `translateX(${translateX}px)`;
                langSlider.textContent = this.currentLang.toUpperCase();
            });
        }
    }

    updateLanguage() {
        const translations = this.translations[this.currentLang];

        // Update all text elements
        Object.keys(translations).forEach(key => {
            const element = document.getElementById(key.replace(/([A-Z])/g, '-$1').toLowerCase());
            if (element) {
                element.textContent = translations[key];
            }
        });

        // Update typewriter if it exists
        const typedElement = document.getElementById('typed-text');
        if (typedElement && window.Typed) {
            typedElement.innerHTML = '';
            new Typed('#typed-text', {
                strings: [translations.typedText],
                typeSpeed: 50,
                showCursor: true,
                cursorChar: '_'
            });
        }
    }

    initScrollAnimations() {
        // Animate elements on scroll
        const observerOptions = {
            threshold: 0.1,
            rootMargin: '0px 0px -50px 0px'
        };

        const observer = new IntersectionObserver((entries) => {
            entries.forEach(entry => {
                if (entry.isIntersecting) {
                    entry.target.style.opacity = '1';
                    entry.target.style.transform = 'translateY(0)';
                }
            });
        }, observerOptions);

        // Observe all sections
        document.querySelectorAll('section').forEach(section => {
            section.style.opacity = '0';
            section.style.transform = 'translateY(50px)';
            section.style.transition = 'all 0.8s ease';
            observer.observe(section);
        });
    }

    initNavigation() {
        const enterBtn = document.getElementById('enterBtn');
        if (enterBtn) {
            enterBtn.addEventListener('click', () => {
                this.navigateToDirectory();
            });
        }
    }

    navigateToDirectory() {
        // Create transition effect
        const overlay = document.createElement('div');
        overlay.className = 'fixed inset-0 bg-black z-50 flex items-center justify-center';
        overlay.innerHTML = `
            <div class="text-center">
                <div class="animate-spin rounded-full h-32 w-32 border-b-2 border-blue-400 mb-4"></div>
                <div class="text-blue-400 text-xl">Entering the Matrix...</div>
            </div>
        `;

        document.body.appendChild(overlay);

        // Animate transition
        anime({
            targets: overlay,
            opacity: [0, 1],
            duration: 500,
            easing: 'easeInOutQuad',
            complete: () => {
                setTimeout(() => {
                    window.location.href = 'directory.html';
                }, 1000);
            }
        });
    }

    initHoverEffects() {
        // Add hover effects to cards
        document.querySelectorAll('.glass-morphism').forEach(card => {
            card.addEventListener('mouseenter', () => {
                anime({
                    targets: card,
                    scale: 1.05,
                    duration: 300,
                    easing: 'easeOutQuad'
                });
            });

            card.addEventListener('mouseleave', () => {
                anime({
                    targets: card,
                    scale: 1,
                    duration: 300,
                    easing: 'easeOutQuad'
                });
            });
        });

        // Electromagnetic pulse effect
        document.querySelectorAll('.electromagnetic-pulse').forEach(btn => {
            btn.addEventListener('click', (e) => {
                const ripple = document.createElement('div');
                ripple.className = 'absolute rounded-full bg-green-400 opacity-30 pointer-events-none';

                const rect = btn.getBoundingClientRect();
                const size = Math.max(rect.width, rect.height);
                ripple.style.width = ripple.style.height = size + 'px';
                ripple.style.left = (e.clientX - rect.left - size / 2) + 'px';
                ripple.style.top = (e.clientY - rect.top - size / 2) + 'px';

                btn.appendChild(ripple);

                anime({
                    targets: ripple,
                    scale: [0, 2],
                    opacity: [0.3, 0],
                    duration: 600,
                    easing: 'easeOutQuad',
                    complete: () => ripple.remove()
                });
            });
        });
    }

    initMouseEffects() {
        // 创建自定义光标
        this.cursor = document.createElement('div');
        this.cursor.className = 'custom-cursor';
        document.body.appendChild(this.cursor);

        // 创建轨迹点
        this.trails = [];
        for (let i = 0; i < 5; i++) {
            const trail = document.createElement('div');
            trail.className = 'cursor-trail';
            document.body.appendChild(trail);
            this.trails.push({
                element: trail,
                x: 0, y: 0,
                delay: i * 3
            });
        }

        // 启用自定义光标
        document.body.classList.add('custom-cursor-enabled');

        // 鼠标移动监听
        document.addEventListener('mousemove', (e) => {
            this.updateCursor(e.clientX, e.clientY);
        });

        // 为交互元素添加悬停效果
        this.initCursorHoverEffects();
    }

    updateCursor(x, y) {
        // 更新主光标
        if (this.cursor) {
            this.cursor.style.left = (x - 10) + 'px';
            this.cursor.style.top = (y - 10) + 'px';
        }

        // 更新轨迹点（延迟效果）
        this.trails.forEach((trail, index) => {
            setTimeout(() => {
                if (trail.element) {
                    trail.element.style.left = (x - 3) + 'px';
                    trail.element.style.top = (y - 3) + 'px';
                }
            }, index * 50);
        });
    }

    initCursorHoverEffects() {
        // 为可交互元素添加悬停效果
        const hoverElements = document.querySelectorAll('button, a, .glass-morphism, .language-toggle');

        hoverElements.forEach(element => {
            element.addEventListener('mouseenter', () => {
                if (this.cursor) {
                    this.cursor.classList.add('hover');
                }
            });

            element.addEventListener('mouseleave', () => {
                if (this.cursor) {
                    this.cursor.classList.remove('hover');
                }
            });
        });
    }

    initGalaxyBackground() {
        // 确保星海背景可见
        const galaxyBg = document.querySelector('.galaxy-bg');
        if (galaxyBg) {
            // 强制设置层级和显示
            galaxyBg.style.zIndex = '-1';
            galaxyBg.style.display = 'block';
            galaxyBg.style.opacity = '1';

            console.log('星海背景已初始化');
        } else {
            console.warn('未找到星海背景元素');
        }

        // 添加额外的星星
        this.createAdditionalStars();
    }

    createAdditionalStars() {
        const starsContainer = document.querySelector('.twinkling-stars');
        if (!starsContainer) return;

        // 清除现有星星
        starsContainer.innerHTML = '';

        // 创建大量随机星星（300颗）
        for (let i = 0; i < 300; i++) {
            const star = document.createElement('div');
            star.style.position = 'absolute';

            // 随机大小
            const size = Math.random() * 3 + 1;
            star.style.width = size + 'px';
            star.style.height = size + 'px';

            // 随机颜色
            const colors = ['#FFFFFF', '#00CCFF', '#FFFF99', '#E6E6FA', '#00FFC6'];
            star.style.background = colors[Math.floor(Math.random() * colors.length)];
            star.style.borderRadius = '50%';

            // 随机位置
            star.style.left = Math.random() * 100 + '%';
            star.style.top = Math.random() * 100 + '%';

            // 随机透明度
            star.style.opacity = Math.random() * 0.8 + 0.2;

            // 随机动画效果
            const animationDuration = Math.random() * 5 + 3;
            const orbitDuration = Math.random() * 30 + 15;
            star.style.animation = `
                starTwinkle ${animationDuration}s infinite alternate,
                starOrbit ${orbitDuration}s linear infinite
            `;

            // 随机轨道半径
            star.style.setProperty('--orbit-radius', Math.random() * 2 + 0.5);

            // 添加发光效果
            star.style.boxShadow = `0 0 ${size * 2}px currentColor`;

            starsContainer.appendChild(star);
        }
    }
}

// Matrix Operations Class
class MatrixOperations {
    static add(matrixA, matrixB) {
        if (!this.isValidMatrix(matrixA) || !this.isValidMatrix(matrixB)) {
            throw new Error('Invalid matrix format');
        }

        if (matrixA.length !== matrixB.length || matrixA[0].length !== matrixB[0].length) {
            throw new Error('Matrix dimensions must match for addition');
        }

        const result = [];
        for (let i = 0; i < matrixA.length; i++) {
            result[i] = [];
            for (let j = 0; j < matrixA[i].length; j++) {
                result[i][j] = matrixA[i][j] + matrixB[i][j];
            }
        }
        return result;
    }

    static multiply(matrixA, matrixB) {
        if (!this.isValidMatrix(matrixA) || !this.isValidMatrix(matrixB)) {
            throw new Error('Invalid matrix format');
        }

        if (matrixA[0].length !== matrixB.length) {
            throw new Error('Invalid matrix dimensions for multiplication');
        }

        const result = [];
        for (let i = 0; i < matrixA.length; i++) {
            result[i] = [];
            for (let j = 0; j < matrixB[0].length; j++) {
                let sum = 0;
                for (let k = 0; k < matrixA[0].length; k++) {
                    sum += matrixA[i][k] * matrixB[k][j];
                }
                result[i][j] = sum;
            }
        }
        return result;
    }

    static determinant(matrix) {
        if (!this.isValidMatrix(matrix) || matrix.length !== matrix[0].length) {
            throw new Error('Matrix must be square for determinant calculation');
        }

        const n = matrix.length;
        if (n === 1) return matrix[0][0];
        if (n === 2) return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

        // Laplace expansion for larger matrices
        let det = 0;
        for (let j = 0; j < n; j++) {
            det += matrix[0][j] * this.cofactor(matrix, 0, j);
        }
        return det;
    }

    static cofactor(matrix, row, col) {
        const subMatrix = [];
        for (let i = 0; i < matrix.length; i++) {
            if (i === row) continue;
            const newRow = [];
            for (let j = 0; j < matrix[i].length; j++) {
                if (j === col) continue;
                newRow.push(matrix[i][j]);
            }
            subMatrix.push(newRow);
        }
        return Math.pow(-1, row + col) * this.determinant(subMatrix);
    }

    static inverse(matrix) {
        const det = this.determinant(matrix);
        if (det === 0) {
            throw new Error('Matrix is singular and cannot be inverted');
        }

        const n = matrix.length;
        const cofactorMatrix = [];

        for (let i = 0; i < n; i++) {
            cofactorMatrix[i] = [];
            for (let j = 0; j < n; j++) {
                cofactorMatrix[i][j] = this.cofactor(matrix, i, j);
            }
        }

        const adjugate = this.transpose(cofactorMatrix);
        return this.scalarMultiply(adjugate, 1 / det);
    }

    static transpose(matrix) {
        const result = [];
        for (let i = 0; i < matrix[0].length; i++) {
            result[i] = [];
            for (let j = 0; j < matrix.length; j++) {
                result[i][j] = matrix[j][i];
            }
        }
        return result;
    }

    static scalarMultiply(matrix, scalar) {
        const result = [];
        for (let i = 0; i < matrix.length; i++) {
            result[i] = [];
            for (let j = 0; j < matrix[i].length; j++) {
                result[i][j] = matrix[i][j] * scalar;
            }
        }
        return result;
    }

    static rank(matrix) {
        // Convert to row echelon form and count non-zero rows
        const temp = matrix.map(row => [...row]);
        const rows = temp.length;
        const cols = temp[0].length;
        let rank = 0;

        for (let row = 0; row < rows; row++) {
            // Find pivot
            let pivot = -1;
            for (let col = 0; col < cols; col++) {
                if (Math.abs(temp[row][col]) > 1e-10) {
                    pivot = col;
                    break;
                }
            }

            if (pivot !== -1) {
                rank++;
                // Eliminate below
                for (let i = row + 1; i < rows; i++) {
                    const factor = temp[i][pivot] / temp[row][pivot];
                    for (let j = pivot; j < cols; j++) {
                        temp[i][j] -= factor * temp[row][j];
                    }
                }
            }
        }

        return rank;
    }

    static isValidMatrix(matrix) {
        if (!Array.isArray(matrix) || matrix.length === 0) return false;
        const cols = matrix[0].length;
        return matrix.every(row => Array.isArray(row) && row.length === cols);
    }

    static parseMatrix(input) {
        try {
            const rows = input.trim().split('\n');
            return rows.map(row =>
                row.trim().split(/\s+|,\s*/).map(x => parseFloat(x))
            );
        } catch (error) {
            throw new Error('Invalid matrix format. Use rows with space or comma-separated numbers.');
        }
    }

    static formatMatrix(matrix) {
        return matrix.map(row =>
            row.map(x => x.toFixed(4)).join(' ')
        ).join('\n');
    }
}

// Utility Functions
class Utils {
    static showNotification(message, type = 'info') {
        const notification = document.createElement('div');
        notification.className = `fixed top-20 right-6 p-4 rounded-lg z-50 transition-all duration-300 ${type === 'error' ? 'bg-red-600 text-white' :
            type === 'success' ? 'bg-green-600 text-white' :
                'bg-blue-600 text-white'
            }`;
        notification.textContent = message;

        document.body.appendChild(notification);

        // Animate in
        anime({
            targets: notification,
            translateX: [300, 0],
            opacity: [0, 1],
            duration: 300,
            easing: 'easeOutQuad'
        });

        // Remove after 3 seconds
        setTimeout(() => {
            anime({
                targets: notification,
                translateX: 300,
                opacity: 0,
                duration: 300,
                easing: 'easeInQuad',
                complete: () => notification.remove()
            });
        }, 3000);
    }

    static validateInput(value, type) {
        switch (type) {
            case 'number':
                return !isNaN(parseFloat(value)) && isFinite(value);
            case 'matrix':
                try {
                    MatrixOperations.parseMatrix(value);
                    return true;
                } catch {
                    return false;
                }
            default:
                return true;
        }
    }

    static formatNumber(num, decimals = 4) {
        return parseFloat(num.toFixed(decimals));
    }
}

// Initialize the application
document.addEventListener('DOMContentLoaded', () => {
    window.linearAlgebraWorld = new LinearAlgebraWorld();

    // Add smooth scrolling
    document.querySelectorAll('a[href^="#"]').forEach(anchor => {
        anchor.addEventListener('click', function (e) {
            e.preventDefault();
            const target = document.querySelector(this.getAttribute('href'));
            if (target) {
                target.scrollIntoView({
                    behavior: 'smooth',
                    block: 'start'
                });
            }
        });
    });

    // Add loading animation
    window.addEventListener('load', () => {
        document.body.classList.add('loaded');

        // Animate hero elements
        anime.timeline()
            .add({
                targets: '.earth-container',
                scale: [0, 1],
                opacity: [0, 1],
                duration: 1000,
                easing: 'easeOutElastic(1, .8)'
            })
            .add({
                targets: 'h1',
                translateY: [50, 0],
                opacity: [0, 1],
                duration: 800,
                easing: 'easeOutQuad'
            }, '-=500')
            .add({
                targets: '.glass-morphism',
                translateY: [30, 0],
                opacity: [0, 1],
                duration: 600,
                delay: anime.stagger(100),
                easing: 'easeOutQuad'
            }, '-=400');
    });
});

// Export for use in other files
if (typeof module !== 'undefined' && module.exports) {
    module.exports = { LinearAlgebraWorld, MatrixOperations, Utils };
}